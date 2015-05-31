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
#define MAX_INT_NUMBERS 12

struct SaveStrings{
	struct SaveStrings *next;
	char *value;
	int id;
};

int index_string_name;
int index_variable_name;
struct SaveStrings *string_list;
SymbolTableLine *globalTableLine;

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
void findVarFunction(SymbolTableLine *symbolTableLine);
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


void generateProgram(Program *program, SymbolTableHeader *symbolTableHeader){
	SymbolTableLine *temp;

	temp = symbolTableHeader->symbolTableLine;

	/* global variables */
	index_string_name = 1;
	index_variable_name = 2;
	string_list = NULL;
	globalTableLine = temp;

	declarePrint();
	printAllStrings(program);

	while(temp != NULL){
		if(typeFunctionGlobalTable(temp->type)){
			createHeaderFunction(temp->name, program, symbolTableHeader);			
		}

		else{
			printGlobalVariable(temp);
		}

		temp = temp->next;
	}

	printHeaderFunction("i32", "main");
	printf(") {\n");

	printf("  %%1 = alloca i32\n");
	printf("  store i32 0, i32* %%1\n");

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
	char *temp;
	size_t size;

	size = strlen(str) - 2;

	temp = (char *)malloc(sizeof(char) * size);
	strncpy(temp, str + 1, size);
	strcpy(str, temp);
	free(temp);

	return str;
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
	}	
}

void createHeaderFunction(char *name, Program *program, SymbolTableHeader *symbolTableHeader){
	SymbolTableHeader *table;

	name = to_lower_case(name);
	table = findTableFunction(name, symbolTableHeader->next);
	printHeaderFunction(varTypeTable(table->symbolTableLine->type), name);
	findVarFunction(findParamFunction(table->symbolTableLine->next));
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
		if(strcmp(temp->flag, "varparam") == 0){
			printf("%s %%%s", varTypeTable(temp->type), temp->name);
		}

		else{
			printf("%s* %%%s", varTypeTable(temp->type), temp->name);
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

void findVarFunction(SymbolTableLine *symbolTableLine){
	SymbolTableLine *temp;

	temp = symbolTableLine;

	while(temp != NULL){
		printVarFunction(temp->name, varTypeTable(temp->type));
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

	if(program != NULL){
		if(strcmp(program->type, "WriteLn") == 0){
			searchWriteLn(program->son, symbolTableLine);			
		}

		else if(strcmp(program->type, "Assign") == 0){
			assign_value = rightAssignFunction(program->son->brother, symbolTableLine);

			aux = (char*) malloc(sizeof(char) * BUFFER);
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

			if(strcmp(program->son->brother->type, "Id") == 0 &&
			   strcmp(to_lower_case(program->son->brother->value), "true") != 0 &&
			   strcmp(to_lower_case(program->son->brother->value), "false") != 0){				

				aux2 = (char*) malloc(sizeof(char) * BUFFER);
				line2 = findGlobalLine(to_lower_case(program->son->brother->value));
				aux2[0] = '@';

				if(line2 == NULL){
					line2 = symbolTableLine;
					
					while(line2 != NULL && strcmp(to_lower_case(program->son->brother->value), line2->name) != 0){
						line2 = line2->next;
					}
					
					aux2[0] = '%';
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

				free(aux2);
				printf("  store %s %%%d, %s* %s\n", varTypeTable(line->type), index_variable_name - 1, varTypeTable(line->type), aux);
			}

			else{
				printf("  store %s %s, %s* %s\n", varTypeTable(line->type), assign_value, varTypeTable(line->type), aux);
			}

			free(aux);			
		}

		searchInMain(program->son, symbolTableLine);
		searchInMain(program->brother, symbolTableLine);
	}
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

	strcpy(assign_value, temp);
	free(temp);

	return assign_value;
}

void searchWriteLn(Program *program, SymbolTableLine *symbolTableLine){
	Program *auxP;
	char *temp, *aux;
	SymbolTableLine *line;

	auxP = program;
	
	while(auxP != NULL){
		if(strcmp(auxP->type, "String") == 0){
			printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([%d x i8]* @.str%d, i32 0, i32 0))\n", index_variable_name++, (int)strlen(auxP->value) + 1, findId(auxP->value));
		}

		else if(strcmp(auxP->type, "IntLit") == 0){
			printWriteLnId(SIZE_INT, "@.strInt", "i32", auxP->value);
		}

		else if(strcmp(auxP->type, "RealLit") == 0){
			printWriteLnId(SIZE_DOUBLE, "@.strDouble", "double", auxP->value);
		}

		else{
			if(strcmp(to_lower_case(auxP->value), "true") == 0){
				printWriteLnId(SIZE_TRUE, "@.strTrue", "i1", auxP->value);
			}
			
			else if(strcmp(to_lower_case(auxP->value), "false") == 0){
				printWriteLnId(SIZE_FALSE, "@.strFalse", "i1", auxP->value);
			}

			else if(strcmp(auxP->type, "Id") == 0){
				aux = (char *)calloc(1, sizeof(char) * BUFFER);
				line = findGlobalLine(to_lower_case(auxP->value));
				strcpy(aux, "@");

				if(line == NULL){
					line = symbolTableLine;
					
					while(line != NULL && strcmp(to_lower_case(auxP->value), line->name) != 0){
						line = line->next;
					}
					
					strcpy(aux, "%");
				}

				strcat(aux, to_lower_case(auxP->value));				

				printf("  %%%d = load %s* %s\n", index_variable_name, varTypeTable(line->type), aux);
				free(aux);

				temp = (char *)calloc(1, sizeof(char) * MAX_INT_NUMBERS);

				sprintf(temp, "%%%d", index_variable_name);
				++index_variable_name;

				if(strcmp(line->type, "_integer_") == 0){
					printWriteLnId(SIZE_INT, "@.strInt", "i32", temp);
				}

				else if(strcmp(line->type, "_boolean_") == 0){
					/* TODO: verify if it's true or false*/
					printWriteLnId(SIZE_TRUE, "@.strTrue", "i1", temp);
				}

				else{
					printWriteLnId(SIZE_DOUBLE, "@.strDouble", "double", temp);
				}

				free(temp);
			}

			else{
				rightAssignFunction(auxP->son, symbolTableLine);
			}
		}

		auxP = auxP->brother;		
	}

	printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @.strNewLine, i32 0, i32 0))\n", index_variable_name++);
}

void printWriteLnId(int size, char *id, char *type, char *value){
	printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([%d x i8]* %s, i32 0, i32 0), %s %s)\n", index_variable_name++, size, id, type, value);
}

char *operations_function(char *op_name, Program *program, SymbolTableLine *symbolTableLine){
	int registry1, registry2;
	Program *temp;
	char *aux;
	char *var1, *var2;
	
	temp = program->son;
	registry1 = registry2 = 0;
	aux = (char*) malloc(sizeof(char) * BUFFER);

	//se o 1º filho da operação é simbolo terminal
	if(hasTerminalSymbol(temp->type)){
		var1 = rightAssignFunction(temp, symbolTableLine);
		registry1 = index_variable_name;
		
		printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(symbolTableLine->type), var1);
		
		if(hasTerminalSymbol(temp->brother->type) == 0){
			var2 = rightAssignFunction(temp->brother, symbolTableLine);
			registry2 = index_variable_name;
			printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(symbolTableLine->type), var2);
		}
		
		else{
			var2 = rightAssignFunction(temp->brother, symbolTableLine);
		}
	}

	//se o 1º filho da operação não é simbolo terminal
	else{
		var1 = rightAssignFunction(temp, symbolTableLine);
		registry1 = index_variable_name - 1;
		
		if(hasTerminalSymbol(temp->brother->type) == 0){
			var2 = rightAssignFunction(temp->brother, symbolTableLine);
			registry2 = index_variable_name;
			printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(symbolTableLine->type), var2);
		}
		
		else{
			var2 = rightAssignFunction(temp->brother, symbolTableLine);
		}
	}	
	
	if(registry1 == 0){
		sprintf(var1, "%%%d", index_variable_name - 1);
	}

	else{
		sprintf(var1, "%%%d", registry1);
	}

	if(registry2 == 0){
		sprintf(var2, "%%%d", index_variable_name - 1);
	}
	
	else{
		sprintf(var2, "%%%d", registry2);
	}	

	if(strcmp(symbolTableLine->type, "_real_") == 0){
		printf("  %%%d = f%s %s %s, %s\n", index_variable_name++, op_name, varTypeTable(symbolTableLine->type), var1, var2);
	}

	else{
		printf("  %%%d = %s %s %s, %s\n", index_variable_name++, op_name, varTypeTable(symbolTableLine->type), var1, var2);
	}

	free(var1);
	free(var2);

	if(aux[0] == '%'){
		sprintf(aux, "%d", index_variable_name - 1);
	}
	
	else{
		sprintf(aux, "%%%d", index_variable_name - 1);
	}
	
	return aux;
}

char *rightAssignFunction(Program *program, SymbolTableLine *symbolTableLine){
	SymbolTableLine *line;
	char *aux;	

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

	aux = (char*) malloc(sizeof(char) * BUFFER);

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


int hasTerminalSymbol(char* type){
	if(strcmp(type, "IntLit") == 0 || strcmp(type, "RealLit") == 0 || strcmp(type, "Id") == 0){
		return 1;
	}

	return 0;
}

SymbolTableLine *findGlobalLine(char *name){
	SymbolTableLine *temp;

	temp = globalTableLine;

	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			return temp;
		}
		
		temp = temp->next;
	}

	return NULL;
}

#endif
