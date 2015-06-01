#ifndef _GENERATOR_
#define _GENERATOR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "semantic.h"

#define SIZE_INT 3
#define SIZE_DOUBLE 6
#define SIZE_FALSE 6
#define SIZE_TRUE 5
#define BUFFER 1024
#define MAX_INT_NUMBERS 13

struct SaveStrings{
	struct SaveStrings *next;
	char *value;
	int id;
};

struct BooleanValue{
	struct BooleanValue *next;
	int value;
	char *name;
	char *function;
};

int index_string_name;
int index_variable_name;
struct SaveStrings *string_list;
struct BooleanValue *boolean_list;
SymbolTableLine *globalTableLine;
int type_to_print;
char *actual_function;

/*Functions*/
void generateProgram(Program *program, SymbolTableHeader *symbolTableHeader);
void declarePrint();
void printAllStrings(Program *program);
char *formatString(char *str);
void insert_into_list_string(char *value);
void printString(char *name);
int typeFunctionGlobalTable(char *type);
void printGlobalVariable(SymbolTableLine *symbolTableLine);
void createHeaderFunction(char *name, Program *program, SymbolTableHeader *symbolTableHeader);
SymbolTableHeader *findTableFunction(char *name, SymbolTableHeader *symbolTableHeader);
void printHeaderFunction(char *type, char *name);
SymbolTableLine *findParamFunction(SymbolTableLine *symbolTableLine);
void findVarFunction(SymbolTableLine *symbolTableLine, char *function);
void printVarFunction(char *name, char *type);
Program *findFunction(Program *program, char *name);
void printReturnFunction(char *type, char *name);
char *varTypeTable(char *type);
int findId(char *value);
Program *findMain(Program *program);
void searchInMain(Program *program, SymbolTableLine *symbolTableLine);
void searchWriteLn(Program *program, SymbolTableLine *symbolTableLine);
void printWriteLnId(int size, char *id, char *type, char *value);
char *rightAssignFunction(Program *program, SymbolTableLine *symbolTableLine);
int hasTerminalSymbol(char *type);
SymbolTableLine *findGlobalLine(char *name);
char *operations_function(char *op_name, Program *program, SymbolTableLine *symbolTableLine);
char *insertPoint(char *assign_value);
int searchValue(char *name, char *function);
int replaceValue(char *name, int value, char *function);
void insertValue(char *name, int value, char *function);
char *return_expr_operation(char *expr);
void print_expression(Program *program, SymbolTableLine *line, char* var1, char* var2);


void generateProgram(Program *program, SymbolTableHeader *symbolTableHeader){
	SymbolTableLine *temp;

	temp = symbolTableHeader->symbolTableLine;

	/* global variables */
	index_string_name = 1;
	index_variable_name = 4;
	string_list = NULL;
	boolean_list = NULL;
	globalTableLine = symbolTableHeader->symbolTableLine;
	actual_function = (char *)calloc(1, sizeof(char) * BUFFER);

	declarePrint();
	printAllStrings(program);

	while(temp != NULL){
		if(typeFunctionGlobalTable(temp->type)){
			strcpy(actual_function, temp->name);
			createHeaderFunction(temp->name, program, symbolTableHeader);		
		}

		else{
			printGlobalVariable(temp);
		}

		temp = temp->next;
	}

	//printf("declare i32 @atoi(i8*)\n");

	printHeaderFunction("i32", "main");
	printf("i32 %%paramcount, i8** %%paramstr) {\n");

	printf("  %%1 = alloca i32\n");	
	printf("  %%2 = alloca i32\n");	
	printf("  %%3 = alloca i8**\n");
	printf("  store i32 0, i32* %%1\n");
	printf("  store i32 %%paramcount, i32* %%2\n");
	printf("  store i8** %%paramstr, i8*** %%3\n");

	strcpy(actual_function, "main");
	searchInMain(findMain(program), symbolTableHeader->symbolTableLine);
	printReturnFunction("i32", "0");
}

void declarePrint(){
	printf("; Default Declarations\n");
	printf("@.strNewLine = private unnamed_addr constant [2 x i8] c\"\\0A\\00\"\n");
	printf("@.strInt = private unnamed_addr constant [3 x i8] c\"%%d\\00\"\n");
	printf("@.strDouble = private unnamed_addr constant [6 x i8] c\"%%.12E\\00\"\n");
	printf("@.str = private unnamed_addr constant [3 x i8] c\"%%s\\00\"\n");
	printf("@.strTrue = private unnamed_addr constant [5 x i8] c\"TRUE\\00\"\n");
	printf("@.strFalse = private unnamed_addr constant [6 x i8] c\"FALSE\\00\"\n");
	printf("\n");

	printf("; Print Declaration\n");
	printf("declare i32 @printf(i8*, ...)\n");
	printf("\n");
}

void printAllStrings(Program *program){
	if(program != NULL){
		if(strcmp(program->type, "String") == 0){
			program->value = formatString(program->value);
			insert_into_list_string(program->value);			
		}

		printAllStrings(program->son);
		printAllStrings(program->brother);
	}
}

char *formatString(char *str){
	unsigned int i, j;
	char *temp;
	size_t size;

	size = strlen(str) - 2;

	temp = (char *)malloc(sizeof(char) * size);
	
	for(i = 1, j = 0; i <= size; ++i, ++j){
		temp[j] = str[i];

		if(str[i] == '\''){
			if(i + 1 <= size){
				if(str[i + 1] == '\''){
					++i;
				}
			}
		}
	}

	return temp;
}

void insert_into_list_string(char *value){
	struct SaveStrings *new, *aux;

	if(string_list == NULL){
		string_list = (struct SaveStrings *)calloc(1, sizeof(struct SaveStrings));
		string_list->value = value;
		string_list->id = index_string_name;
	}

	else{
		aux = string_list;
		new = (struct SaveStrings *)calloc(1, sizeof(struct SaveStrings));

		if(strcmp(value, aux->value) == 0){
			return;
		}

		while(aux->next != NULL){
			if(strcmp(value, aux->value) == 0){
				return;
			}

			aux = aux->next;
		}

		new->value = value;
		new->id = index_string_name;
		aux->next = new;
	}

	printString(value);
}

void printString(char *name){
	printf("@.str%d = private unnamed_addr constant [%d x i8] c\"%s\\00\"\n", index_string_name++, (int)strlen(name) + 1, name);
}

int typeFunctionGlobalTable(char *type){
	return (strcmp(type, "_function_") == 0) ? 1 : 0;
}

void printGlobalVariable(SymbolTableLine *symbolTableLine){
	char *temp;

	temp = varTypeTable(symbolTableLine->type);

	if(strcmp(temp, "double") == 0){
		printf("@%s = common global %s 0.0\n", symbolTableLine->name, temp);
	}

	else{
		printf("@%s = common global %s 0\n", symbolTableLine->name, temp);

		if(strcmp(temp, "i1") == 0){
			insertValue(symbolTableLine->name, 0, "main");
		}
	}	
}

void createHeaderFunction(char *name, Program *program, SymbolTableHeader *symbolTableHeader){
	SymbolTableHeader *table;

	name = to_lower_case(name);
	table = findTableFunction(name, symbolTableHeader->next);
	printHeaderFunction(varTypeTable(table->symbolTableLine->type), name);
	findVarFunction(findParamFunction(table->symbolTableLine->next), symbolTableHeader->symbolTableLine->name);
	searchInMain(findFunction(program, name), table->symbolTableLine);
	printReturnFunction(varTypeTable(table->symbolTableLine->type), "0");
}

SymbolTableHeader *findTableFunction(char *name, SymbolTableHeader *symbolTableHeader){
	SymbolTableHeader *temp;

	temp = symbolTableHeader;
	name = to_lower_case(name);

	while(temp != NULL){
		if(strcmp(name, temp->symbolTableLine->name) == 0){
			return temp;
		}

		temp = temp->next;
	}
	
	return NULL;
}

void printHeaderFunction(char *type, char *name){
	printf("\ndefine %s @%s(", type, name);
}

SymbolTableLine *findParamFunction(SymbolTableLine *symbolTableLine){
	SymbolTableLine *temp;

	if(symbolTableLine == NULL){
		printf(") {\n");
		return NULL;
	}

	temp = symbolTableLine;

	while(1){
		if(temp->flag != NULL){
			if(strcmp(temp->flag, "varparam") == 0){
				printf("%s %%%s", varTypeTable(temp->type), temp->name);
			}

			else{
				printf("%s* %%%s", varTypeTable(temp->type), temp->name);
			}
		}

		temp = temp->next;

		if(temp != NULL && temp->flag != NULL){
			printf(", ");
		}

		else{
			printf(") {\n");
			break;
		}
	}

	return temp;
}

void findVarFunction(SymbolTableLine *symbolTableLine, char *function){
	SymbolTableLine *temp;

	temp = symbolTableLine;

	while(temp != NULL){
		printVarFunction(temp->name, varTypeTable(temp->type));

		if(strcmp(temp->type, "_boolean_") == 0){
			insertValue(temp->name, 0, function);
		}

		temp = temp->next;
	}
}

void printVarFunction(char *name, char *type){
	printf("  %%%s = alloca %s\n", name, type);
}

Program *findFunction(Program *program, char *name){
	Program *aux;

	/* goes to the son of FUNCPART, to find the function name */
	aux = program->brother;
	name = to_lower_case(name);

	while(strcmp(aux->type, "FuncPart") != 0){
		aux = aux->brother;
	}

	while(strcmp(to_lower_case(aux->son->son->value), name) != 0){
		aux = aux->brother;
	}

	return aux->son->son->brother;
}

void printReturnFunction(char *type, char *name){
	printf("  ret %s %s\n}\n", type, name);
}

char *varTypeTable(char *type){
	if(strcmp(type, "_integer_") == 0){
		return "i32";
	}

	if(strcmp(type, "_boolean_") == 0){
		return "i1";
	}

	return "double";
}

int findId(char *value){
	struct SaveStrings *aux;

	aux = string_list;

	while(strcmp(value, aux->value) != 0){
		aux = aux->next;
	}

	return aux->id;
}

Program *findMain(Program *program){
	Program *aux;

	aux = program->brother;

	while(strcmp(aux->type, "FuncPart") != 0){
		aux = aux->brother;
	}

	while(strcmp(aux->type, "NoPrint") == 0){
		aux = aux->brother;
	}

	return aux;
}

void searchInMain(Program *program, SymbolTableLine *symbolTableLine){
	SymbolTableLine *line, *line2;
	char *aux, *aux2;
	char *assign_value;

	aux = (char*) malloc(sizeof(char) * BUFFER);
	aux2 = (char*) malloc(sizeof(char) * BUFFER);

	if(program != NULL){
		if(strcmp(program->type, "WriteLn") == 0){
			searchWriteLn(program, symbolTableLine);			
		}

		else if(strcmp(program->type, "Assign") == 0){
			assign_value = rightAssignFunction(program->son->brother, symbolTableLine);
			
			line = findGlobalLine(to_lower_case(program->son->value));			
			strcpy(aux, "@");

			if(line == NULL){
				line = symbolTableLine;
				
				while(line != NULL && strcmp(to_lower_case(program->son->value), line->name) != 0){
					line = line->next;				
				}

				strcpy(aux, "%");
			}

			strcat(aux, to_lower_case(program->son->value));

			if(strcmp(line->type, "_real_") == 0 && !strchr(assign_value, '.')){
				if(strchr(assign_value, 'e')){
					assign_value = insertPoint(assign_value);
				}

				else{
					strcat(assign_value, ".0");
				}
			}			

			if(strcmp(program->son->brother->type, "Id") == 0){
				if(strcmp(to_lower_case(program->son->brother->value), "false") == 0){
					if(!replaceValue(program->son->value, 0, actual_function)){
						replaceValue(program->son->value, 0, "main");
					}

					printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line->type), rightAssignFunction(program->son, line));
					printf("  store %s %s, %s* %s\n", varTypeTable(line->type), assign_value, varTypeTable(line->type), aux);
				}

				else if(strcmp(to_lower_case(program->son->brother->value), "true") == 0){
					if(!replaceValue(program->son->value, 1, actual_function)){
						replaceValue(program->son->value, 1, "main");
					}

					printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line->type), rightAssignFunction(program->son, line));
					printf("  store %s %s, %s* %s\n", varTypeTable(line->type), assign_value, varTypeTable(line->type), aux);
				}
				
				else{
					if(strcmp(line->type, "_boolean_") == 0){
						if(searchValue(program->son->brother->value, actual_function) == -1){
							if(!replaceValue(program->son->value, searchValue(program->son->brother->value, "main"), actual_function)){
								replaceValue(program->son->value, searchValue(program->son->brother->value, "main"), "main");
							}						
						}

						if(!replaceValue(program->son->value, searchValue(program->son->brother->value, actual_function), actual_function)){
							replaceValue(program->son->value, searchValue(program->son->brother->value, actual_function), "main");
						}
					}

					line2 = findGlobalLine(to_lower_case(program->son->brother->value));
					strcpy(aux2, "@");

					if(line2 == NULL){
						line2 = symbolTableLine;
						
						while(line2 != NULL && strcmp(to_lower_case(program->son->brother->value), line2->name) != 0){
							line2 = line2->next;
						}
						
						strcpy(aux2, "%");
					}

					strcat(aux2, to_lower_case(program->son->brother->value));

					if(strcmp(line2->type, "_integer_") == 0 && strcmp(line->type, "_real_") == 0){					
						printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line2->type), rightAssignFunction(program->son->brother, line2));
						printf("  %%%d = sitofp i32 %%%d to double\n", index_variable_name, index_variable_name - 1);
						++index_variable_name;
					}

					else{
						printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line2->type), aux2);
					}

					printf("  store %s %%%d, %s* %s\n", varTypeTable(line->type), index_variable_name - 1, varTypeTable(line->type), aux);
				}
			}

			else{
				printf("  store %s %s, %s* %s\n", varTypeTable(line->type), assign_value, varTypeTable(line->type), aux);
			}		
		}

		else if(strcmp(program->type, "IfElse") == 0){
			Program *op = program->son;
			Program *ex = op->son;
			char *var1 = (char*) malloc(sizeof(char) * BUFFER);
			char *var2 = (char*) malloc(sizeof(char) * BUFFER);

			while(ex != NULL){
				if(strcmp(ex->type,"Id")==0){
					line = findGlobalLine(to_lower_case(ex->value));			
					strcpy(aux, "@");
					if(line == NULL){
						line = symbolTableLine;
						
						while(line != NULL && strcmp(to_lower_case(ex->value), line->name) != 0){
							line = line->next;				
						}

						strcpy(aux, "%");
					}
					strcat(aux, to_lower_case(ex->value));
					printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line->type), aux);
					
					strcpy(aux, "%");
					sprintf(aux2, "%d", index_variable_name - 1);
					strcat(aux,aux2);

					if(strcmp(var1,"")==0)
						strcpy(var1, aux);
					else{
						strcpy(var2, aux);
					}
				}

				else if(strcmp(var1,"")==0){
					strcpy(var1,ex->value);
				}

				else if(strcmp(var2,"")==0){
					strcpy(var2,ex->value);
				}
				ex = ex->brother;
			}


			print_expression(op, line, var1, var2);
			program = program->brother;

		}

		if(program!=NULL){
			searchInMain(program->son, symbolTableLine);
			searchInMain(program->brother, symbolTableLine);
		}
	}
}

void print_expression(Program *program, SymbolTableLine *line, char* var1, char* var2){
	int registry = index_variable_name;
	printf("  %%%d = icmp %s %s %s, %s\n", index_variable_name++, return_expr_operation(program->type), varTypeTable(line->type), var1, var2);
	printf("  br i1 %%%d, label %%%d, label %%%d\n", registry, registry + 1, registry + 2);
	index_variable_name += 2;
	printf("\n  ; <label>:%d\n", registry+1);
	searchInMain(program->brother, line);
	printf("  br label %%%d\n", registry+2);
	printf("\n  ; <label>:%d\n", registry+2);
}

char *insertPoint(char *assign_value){
	unsigned int i, j;
	char *temp;

	temp = (char *)calloc(1, sizeof(char) * strlen(assign_value) + 2);

	for(i = j = 0; i < strlen(assign_value); ++i, ++j){
		if(assign_value[i] == 'e'){
			temp[j++] = '.';
			temp[j++] = '0';
			temp[j] = 'e';
		}

		else{
			temp[j] = assign_value[i];
		}
	}

	return temp;
}

void searchWriteLn(Program *program, SymbolTableLine *symbolTableLine){
	Program *auxP;
	char temp[MAX_INT_NUMBERS], *aux;
	SymbolTableLine *line;

	auxP = program;
	aux = (char *)calloc(1, sizeof(char) * BUFFER);
	
	while(auxP->son != NULL){
		if(strcmp(auxP->son->type, "String") == 0){
			printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([%d x i8]* @.str%d, i32 0, i32 0))\n", index_variable_name++, (int)strlen(auxP->son->value) + 1, findId(auxP->son->value));
		}

		else if(strcmp(auxP->son->type, "IntLit") == 0){
			printWriteLnId(SIZE_INT, "@.strInt", "i32", auxP->son->value);
		}

		else if(strcmp(auxP->son->type, "RealLit") == 0){
			if(!strchr(auxP->son->value, '.')){
				if(strchr(auxP->son->value, 'e')){
					auxP->son->value = insertPoint(auxP->son->value);
				}

				else{
					strcat(auxP->son->value, ".0");
				}
			}

			printWriteLnId(SIZE_DOUBLE, "@.strDouble", "double", auxP->son->value);
		}

		else if(strcmp(to_lower_case(auxP->son->value), "true") == 0){
			printWriteLnId(SIZE_TRUE, "@.strTrue", "i1", auxP->son->value);
		}
		
		else if(strcmp(to_lower_case(auxP->son->value), "false") == 0){
			printWriteLnId(SIZE_FALSE, "@.strFalse", "i1", auxP->son->value);
		}

		else if(strcmp(auxP->son->type, "Id") == 0){
			if(strcmp(to_lower_case(auxP->son->value), "paramcount") == 0){
				printWriteLnId(SIZE_INT, "@.strInt", "i32", "%paramcount");
			}

			else{
				line = findGlobalLine(to_lower_case(auxP->son->value));
				strcpy(aux, "@");

				if(line == NULL){
					line = symbolTableLine;
					
					while(line != NULL && strcmp(to_lower_case(auxP->son->value), line->name) != 0){
						line = line->next;
					}
					
					strcpy(aux, "%");
				}

				strcat(aux, to_lower_case(auxP->son->value));			

				printf("  %%%d = load %s* %s\n", index_variable_name, varTypeTable(line->type), aux);

				sprintf(temp, "%%%d", index_variable_name);
				++index_variable_name;

				if(strcmp(line->type, "_integer_") == 0){
					printWriteLnId(SIZE_INT, "@.strInt", "i32", temp);
				}

				else if(strcmp(line->type, "_boolean_") == 0){
					// TODO: verify if it's true or false
					
					if(searchValue(auxP->son->value, actual_function)){
						printWriteLnId(SIZE_TRUE, "@.strTrue", "i1", temp);	
					}

					else{
						printWriteLnId(SIZE_FALSE, "@.strFalse", "i1", temp);
					}
				}

				else{
					printWriteLnId(SIZE_DOUBLE, "@.strDouble", "double", temp);
				}
			}
		}

		else{
			aux = rightAssignFunction(auxP->son, symbolTableLine);
			//printWriteLnId(, , , aux);
		}

		auxP->son = auxP->son->brother;		
	}

	printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @.strNewLine, i32 0, i32 0))\n", index_variable_name++);
}

void printWriteLnId(int size, char *id, char *type, char *value){
	printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([%d x i8]* %s, i32 0, i32 0), %s %s)\n", index_variable_name++, size, id, type, value);
}

char *operations_function(char* op_name, Program *program, SymbolTableLine *symbolTableLine){
	int registry1, registry2;
	Program *temp;
	SymbolTableLine *line = symbolTableLine;
	char *aux = (char*) malloc(sizeof(char) * BUFFER);
	char *var1 = (char*) malloc(sizeof(char) * BUFFER);
	char *var2 = (char*) malloc(sizeof(char) * BUFFER);
	
	temp = program;
	registry1 = 0;
	registry2 = 0;

	//se o 1º filho da operação é simbolo terminal
	if(hasTerminalSymbol(program->son->type)==0){
		temp=temp->son;
		var1 = rightAssignFunction(temp, line);
		registry1 = index_variable_name;
		printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line->type), var1);
		var2 = rightAssignFunction(temp->brother, line);

		if(hasTerminalSymbol(temp->brother->type)==0){			
			registry2 = index_variable_name;
			printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line->type), var2);
		}
	}

	//se o 1º filho da operação não é simbolo terminal
	else if(hasTerminalSymbol(program->son->type)!=0){
		temp = temp->son;
		var1 = rightAssignFunction(temp, line);
		registry1 = index_variable_name -1 ;
		var2 = rightAssignFunction(temp->brother, line);

		if(hasTerminalSymbol(temp->brother->type)==0){			
			registry2 = index_variable_name;
			printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line->type), var2);
		}
	}

	if(registry1!=0)
		sprintf(var1, "%%%d",registry1);
	if (registry1==0)
		sprintf(var1, "%%%d",index_variable_name-1);
	if(registry2!=0)
		sprintf(var2, "%%%d",registry2);
	if (registry2==0)
		sprintf(var2, "%%%d",index_variable_name-1);
			

	if(strcmp(line->type, "_integer_") == 0){
		printf("  %%%d = %s %s %s, %s\n", index_variable_name++, op_name, varTypeTable(line->type), var1, var2);
	}

	else if(strcmp(line->type, "_real_") == 0){
		printf("  %%%d = f%s %s %s, %s\n", index_variable_name++,op_name, varTypeTable(line->type), var1, var2);
	}

	if(aux[0]=='%')
		sprintf(aux,"%d", index_variable_name-1);
	else
		sprintf(aux,"%%%d", index_variable_name-1);
	return aux;
}

char *rightAssignFunction(Program *program, SymbolTableLine *symbolTableLine){
	SymbolTableLine *line;
	char *aux;	

	aux = (char*) malloc(sizeof(char) * BUFFER);

	if(strcmp(program->type, "Add") == 0){
		return operations_function("add", program, symbolTableLine);
	}

	if(strcmp(program->type, "Sub") == 0){
		return operations_function("sub", program, symbolTableLine);
	}

	if(strcmp(program->type, "Mul") == 0){
		return operations_function("mul", program, symbolTableLine);
	}

	if(strcmp(program->type, "Div") == 0 || strcmp(program->type, "RealDiv") == 0){
		return operations_function("div", program, symbolTableLine);
	}

	if(strcmp(program->type, "Mod") == 0){
		return operations_function("srem", program, symbolTableLine);
	}

	if(strcmp(program->type, "IntLit") == 0 || strcmp(program->type, "RealLit") == 0){ 
		return program->value;
	}

	if(strcmp(to_lower_case(program->value), "true") == 0){
		return "1";
	}

	if(strcmp(to_lower_case(program->value), "false") == 0){
		return "0";
	}

	if(strcmp(program->type, "Id") == 0){
		line = findGlobalLine(to_lower_case(program->value));
		strcpy(aux, "@");

		if(line == NULL){
			line = symbolTableLine;
			
			while(line != NULL && strcmp(to_lower_case(program->value), line->name) != 0){
				line = line->next;
			}
			
			strcpy(aux, "%");
		}		
		
		strcat(aux, to_lower_case(program->value));
		
		return aux;
	}

	return NULL;
}


int hasTerminalSymbol(char* type){
	if(strcmp(type, "IntLit") == 0 || strcmp(type, "RealLit") == 0 || strcmp(type, "Id") == 0){
		return 0;
	}

	return 1;
}

SymbolTableLine *findGlobalLine(char *name){
	SymbolTableLine *temp;

	temp = globalTableLine;

	while(temp != NULL && !typeFunctionGlobalTable(temp->type)){
		if(strcmp(name, temp->name) == 0){
			return temp;
		}
		
		temp = temp->next;
	}

	return NULL;
}

int searchValue(char *name, char *function){
	struct BooleanValue *aux;

	aux = boolean_list;

	while(aux != NULL){
		if(strcmp(to_lower_case(name), aux->name) == 0 && strcmp(function, aux->function) == 0){
			return aux->value;
		}

		aux = aux->next;
	}

	return -1;
}

int replaceValue(char *name, int value, char *function){
	struct BooleanValue *aux;

	aux = boolean_list;

	while(aux != NULL){
		if(strcmp(to_lower_case(name), aux->name) == 0 && strcmp(function, aux->function) == 0){
			aux->value = value;
			return 1;
		}

		aux = aux->next;
	}

	return 0;
}

void insertValue(char *name, int value, char *function){
	struct BooleanValue *new, *aux;

	if(boolean_list == NULL){
		boolean_list = (struct BooleanValue *)calloc(1, sizeof(struct BooleanValue));
		boolean_list->value = value;
		boolean_list->name = name;
		boolean_list->function = function;
	}

	else{
		aux = boolean_list;
		new = (struct BooleanValue *)calloc(1, sizeof(struct BooleanValue));

		while(aux->next != NULL){
			aux = aux->next;
		}

		new->value = value;
		new->name = name;
		new->function = function;
		aux->next = new;
	}
}

char *return_expr_operation(char *expr){
	if(strcmp(expr, "Eq") == 0){
		return "eq";
	}

	if(strcmp(expr, "Gt") == 0){
		return "sgt";
	}

	if(strcmp(expr, "Lt") == 0){
		return "slt";
	}

	if(strcmp(expr, "Neq") == 0){
		return "ne";
	}

	if(strcmp(expr, "Leq") == 0){
		return "sle";
	}

	if(strcmp(expr, "Geq") == 0){
		return "sle";
	}

	return NULL;
}

#endif
