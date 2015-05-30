#ifndef _GENERATOR_
#define _GENERATOR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "semantic.h"

#define SIZE_INT 3
#define SIZE_DOUBLE 6

typedef struct save_strings save_strings;
struct save_strings{
	save_strings *next;
	char *value;
	int id;
};

int index_string_name = 1;
int index_variable_name = 1;
save_strings *string_list = NULL;
SymbolTableLine *globalTableLine;

/*Functions*/
void generateProgram(Program* program, SymbolTableHeader *symbolTableHeader);
void declarePrint();
void printAllStrings(Program *program);
char *formatString(char *str);
void insert_into_list_string(char *value);
void printString(char *name);
int typeFunctionGlobalTable(char *type);
void printGlobalVariable(SymbolTableLine *symbolTableLine);
void createHeaderFunction(char* name, Program *program, SymbolTableHeader *symbolTableHeader);
SymbolTableHeader *findTableFunction(char* name, SymbolTableHeader *symbolTableHeader);
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
void searchWriteLn(Program *program, char *aux, SymbolTableLine *symbolTableLine);
void printWriteLn();
void printWriteLnId(int size, char *id, char *type, char *value);
char *rightAssignFunction(Program *program, SymbolTableLine *symbolTableLine);
int hasTerminalSymbol(char* type);
SymbolTableLine *findGlobalLine(char *name);
char *operations_function(char* op_name, Program *program, SymbolTableLine *symbolTableLine);


void generateProgram(Program* program, SymbolTableHeader *symbolTableHeader){
	Program *aux;
	SymbolTableLine *temp = symbolTableHeader->symbolTableLine;
	globalTableLine = temp;

	declarePrint();
	printAllStrings(program);

	while(symbolTableHeader->symbolTableLine != NULL){
		if(typeFunctionGlobalTable(symbolTableHeader->symbolTableLine->type)){
			createHeaderFunction(symbolTableHeader->symbolTableLine->name, program, symbolTableHeader);			
		}

		else{
			printGlobalVariable(symbolTableHeader->symbolTableLine);
		}

		symbolTableHeader->symbolTableLine = symbolTableHeader->symbolTableLine->next;
	}

	printHeaderFunction("i32", "main");
	printf(") {\n");
	aux = findMain(program);
	searchInMain(aux, temp);
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
			printString(program->value);
		}

		printAllStrings(program->son);
		printAllStrings(program->brother);
	}
}

char *formatString(char *str){
	char *temp;

	temp = (char *)malloc(sizeof(char) * strlen(str) - 2);
	strncpy(temp, str + 1, strlen(str) - 2);

	return temp;
}

void insert_into_list_string(char *value){
	save_strings *new, *aux;

	if(string_list == NULL){
		string_list = (save_strings *)calloc(1, sizeof(save_strings));
		string_list->value = value;
		string_list->id = index_string_name;
	}

	else{
		aux = string_list;
		new = (save_strings *)calloc(1, sizeof(save_strings));

		while(aux->next != NULL){
			aux = aux->next;
		}

		new->value = value;
		new->id = index_string_name;
		aux->next = new;
	}
}

void printString(char *name){
	printf("@.str%d = private unnamed_addr constant [%d x i8] c\"%s\\00\"\n", index_string_name++, (int)strlen(name) + 1, name);
}

int typeFunctionGlobalTable(char *type){
	return (strcmp(type, "_function_") == 0) ? 1 : 0;
}

void printGlobalVariable(SymbolTableLine *symbolTableLine){
	char *temp = varTypeTable(symbolTableLine->type);
	char *value = (char *)calloc(1, sizeof(char) * 6);

	if(strcmp(temp, "double") == 0){
		strcpy(value, "0.000000e+00");
	}

	else{
		strcpy(value, "0");
	}

	printf("@%s = common global %s %s\n", symbolTableLine->name, temp, value);
}

void createHeaderFunction(char *name, Program *program, SymbolTableHeader *symbolTableHeader){
	SymbolTableHeader *table;
	SymbolTableLine *temp;
	Program *aux;

	table = findTableFunction(name, symbolTableHeader->next);
	
	printHeaderFunction(varTypeTable(table->symbolTableLine->type), table->symbolTableLine->name);
	
	temp = findParamFunction(table->symbolTableLine->next);	
	findVarFunction(temp);

	aux = findFunction(program, table->symbolTableLine->name);
	searchInMain(aux, table->symbolTableLine);
	
	printReturnFunction(varTypeTable(table->symbolTableLine->type), "0");
}

SymbolTableHeader *findTableFunction(char *name, SymbolTableHeader *symbolTableHeader){
	SymbolTableLine *line;

	while(symbolTableHeader != NULL){	
		line = symbolTableHeader->symbolTableLine;

		if(strcmp(to_lower_case(name), line->name) == 0){
			return symbolTableHeader;
		}

		symbolTableHeader = symbolTableHeader->next;
	}
	
	return NULL;
}

void printHeaderFunction(char *type, char *name){
	printf("\ndefine %s @%s(", type, name);
}

SymbolTableLine *findParamFunction(SymbolTableLine *symbolTableLine){
	if(symbolTableLine == NULL){
		printf(") {\n");
		return symbolTableLine;
	}

	while(1){
		printf("%s %%%s", varTypeTable(symbolTableLine->type), symbolTableLine->name);

		symbolTableLine = symbolTableLine->next;

		if(symbolTableLine != NULL && symbolTableLine->flag != NULL){
			printf(", ");
		}

		else{
			printf(") {\n");
			break;
		}
	}

	return symbolTableLine;
}

void findVarFunction(SymbolTableLine *symbolTableLine){
	while(symbolTableLine != NULL){
		printVarFunction(symbolTableLine->name, varTypeTable(symbolTableLine->type));

		symbolTableLine = symbolTableLine->next;
	}
}

void printVarFunction(char *name, char *type){
	printf("  %%%s = alloca %s\n", name, type);
}

Program *findFunction(Program *program, char *name){
	Program *aux = program;

	/* goes to the son of FUNCPART, to find the function name */
	aux = aux->brother->brother->son;

	while(strcmp(aux->son->value, name) != 0){
		aux = aux->brother;
	}

	return findMain(aux->son);
	//return NULL;
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
	save_strings *aux = string_list;

	while(strcmp(value, aux->value) != 0){
		aux = aux->next;
	}

	return aux->id;
}

Program *findMain(Program *program){
	Program *aux = program;

	while(strcmp(aux->type, "VarPart") != 0){
		aux = aux->brother;
	}

	aux = aux->brother->brother;

	return aux;
}

void searchInMain(Program *program, SymbolTableLine *symbolTableLine){
	SymbolTableLine *line = symbolTableLine;
	char *aux = (char*) malloc(sizeof(char)*40);

	if(program != NULL){
		if(strcmp(program->type, "WriteLn") == 0){
			searchWriteLn(program->son, aux, line);			
		}

		if(strcmp(program->type, "Assign")==0){
			char *assign_value;

			assign_value = rightAssignFunction(program->son->brother, line);

			line = findGlobalLine(program->son->value);
			strcpy(aux,"@");

			if(line==NULL){
				line = symbolTableLine;
				while(strcmp(program->son->value,line->name)!=0 && line!=NULL){
					line = line->next;
				}
				strcpy(aux,"%");
			}

			strcat(aux,program->son->value);

			if(strcmp(line->type, "_real_") == 0 && !strchr(assign_value, '.')){
				strcat(assign_value, ".0");
			}

			printf("  store %s %s, %s* %s\n",varTypeTable(line->type),assign_value,varTypeTable(line->type),aux);
		}

		searchInMain(program->son, symbolTableLine);
		searchInMain(program->brother, symbolTableLine);
	}
}

void searchWriteLn(Program *program, char *aux, SymbolTableLine *symbolTableLine){
	char temp[17];
	SymbolTableLine *line;

	if(program == NULL){
		printWriteLn();
		printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @.strNewLine, i32 0, i32 0))\n", index_variable_name++);		
	}
	
	while(program != NULL){
		if(strcmp(program->type, "String") == 0){
			/*sprintf(temp2, "@.str%d", findId(program->value));
			printf("  %%%d = load i8** %s\n", index_variable_name, temp2);
			sprintf(temp, "%%%d", index_variable_name);
			++index_variable_name;
			printWriteLnId(3, temp2, "i8*", temp);*/
			printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([%d x i8]* @.str%d, i32 0, i32 0))\n", index_variable_name++, (int)strlen(program->value) + 1, findId(program->value));
		}

		else if(strcmp(program->type, "IntLit") == 0){
			printWriteLnId(SIZE_INT, "@.strInt", "i32", program->value);
		}

		else if(strcmp(program->type, "RealLit") == 0){
			printWriteLnId(SIZE_DOUBLE, "@.strDouble", "double", program->value);
		}

		else{
			if(strcmp(program->value, "true")==0){
				printWriteLnId(5, "@.strTrue", "i1", program->value);
			}
			
			else if(strcmp(program->value, "false")==0){
				printWriteLnId(6, "@.strFalse", "i1", program->value);
			}

			else if(strcmp(program->type, "Id") == 0){
				line = findGlobalLine(program->value);
				strcpy(aux,"@");

				if(line==NULL){
					line = symbolTableLine;
					while(strcmp(program->value,line->name)!=0 && line!=NULL){
						line = line->next;
					}
					strcpy(aux,"%");
				}

				strcat(aux,program->value);				

				printf("  %%%d = load %s* %s\n", index_variable_name, varTypeTable(line->type), aux);
				sprintf(temp, "%%%d", index_variable_name);
				++index_variable_name;

				if(strcmp(line->type, "_integer_")==0){
					printWriteLnId(SIZE_INT, "@.strInt", "i32", temp);
				}

				else if(strcmp(line->type, "_boolean_") == 0){
					printWriteLnId(5, "@.strTrue", "i1", temp);
				}

				else{
					printWriteLnId(SIZE_DOUBLE, "@.strDouble", "double", temp);
				}
			}

			else{
				rightAssignFunction(program->son,symbolTableLine);
			}
		}

		program = program->brother;		
	}

	printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @.strNewLine, i32 0, i32 0))\n", index_variable_name++);
}

void printWriteLn(){
	printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([1 x i8]* @.str, i32 0, i32 0))\n", index_variable_name);
}

void printWriteLnId(int size, char *id, char *type, char *value){
	printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([%d x i8]* %s, i32 0, i32 0), %s %s)\n", index_variable_name++, size, id, type, value);
}


char *operations_function(char* op_name, Program *program, SymbolTableLine *symbolTableLine){
	int registry1, registry2;
	Program *temp;
	SymbolTableLine *line = symbolTableLine;
	char *aux = (char*) malloc(sizeof(char)*40);
	char *var1 = (char*) malloc(sizeof(char)*10);
	char *var2 = (char*) malloc(sizeof(char)*10);
	
	temp = program;
	registry1 = 0;
	registry2 = 0;

	//se o 1º filho da operação é simbolo terminal
	if(hasTerminalSymbol(program->son->type)==0){
		temp=temp->son;
		var1 = rightAssignFunction(temp, line);
		registry1 = index_variable_name;
		printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line->type), var1);
		if(hasTerminalSymbol(temp->brother->type)==0){
			var2 = rightAssignFunction(temp->brother, line);
			registry2 = index_variable_name;
			printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line->type), var2);
		}
		else{
			var2 = rightAssignFunction(temp->brother, line);
		}
	}

	//se o 1º filho da operação não é simbolo terminal
	else if(hasTerminalSymbol(program->son->type)!=0){
		temp = temp->son;
		var1 = rightAssignFunction(temp, line);
		registry1 = index_variable_name -1 ;
		if(hasTerminalSymbol(temp->brother->type)==0){
			var2 = rightAssignFunction(temp->brother, line);
			registry2 = index_variable_name;
			printf("  %%%d = load %s* %s\n", index_variable_name++, varTypeTable(line->type), var2);
		}
		else{
			var2 = rightAssignFunction(temp->brother, line);
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
	Program *temp=program;
	SymbolTableLine *line = symbolTableLine;
	char *aux = (char*) malloc(sizeof(char)*40);

	if(strcmp(program->type, "Add")==0){
		return operations_function("add", program, symbolTableLine);
	}

	if(strcmp(program->type, "Sub")==0){
		return operations_function("sub", program, symbolTableLine);
	}

	if(strcmp(program->type, "Mul")==0){
		return operations_function("mul", program, symbolTableLine);
	}

	if(strcmp(program->type, "Div")==0 || strcmp(program->type, "RealDiv") == 0){
		return operations_function("div", program, symbolTableLine);
	}

	if(strcmp(program->type, "Mod") == 0){
		return operations_function("srem", program, symbolTableLine);
	}

	if(strcmp(program->type, "IntLit")==0 || strcmp(program->type, "RealLit")==0){ 
		return program->value;
	}

	if(strcmp(program->value, "true") == 0){
		return "1";
	}

	if(strcmp(program->value, "false") == 0){
		return "0";
	}

	line = findGlobalLine(temp->value);
	strcpy(aux,"@");

	if(line==NULL){
		line = symbolTableLine;
		
		while(strcmp(temp->value,line->name)!=0 && line!=NULL){
			line = line->next;
		}
		strcpy(aux,"%");
	}		
	strcat(aux, temp->value);
	
	return aux;
}


int hasTerminalSymbol(char* type){
	if(strcmp(type, "IntLit") == 0){
		return 0;
	}

	else if(strcmp(type, "RealLit") == 0){
		return 0;
	}

	else if(strcmp(type, "Id") == 0){
		return 0;
	}

	return 1;
}

SymbolTableLine *findGlobalLine(char *name){
	SymbolTableLine *temp = globalTableLine;

	while(temp!=NULL){
		if(strcmp(name, temp->name)==0)
			return temp;
		temp=temp->next;
	}

	return NULL;
}

#endif
