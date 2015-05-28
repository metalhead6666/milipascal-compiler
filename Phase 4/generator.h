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

int index_string_name = 0;
save_strings *string_list = NULL;

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
void searchInMain(Program *program);
void searchWriteLn(Program *program);
void printWriteLn(int size, char *id, char *value);


void generateProgram(Program* program, SymbolTableHeader *symbolTableHeader){
	Program *aux;

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
	searchInMain(aux);
	printReturnFunction("i32", "0");
}

void declarePrint(){
	printf("; Default Declarations\n");
	printf("@.strNewLine = private unnamed_addr constant [2 x i8] c\"\\0A\\00\"\n");
	printf("@.strInt = private unnamed_addr constant [3 x i8] c\"%%d\\00\"\n");
	printf("@.strDouble = private unnamed_addr constant [6 x i8] c\"%%.12F\\00\"\n");
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
	printf("@.str.%d = private unnamed_addr constant [%d x i8] c\"%s\\00\"\n", index_string_name++, (int)strlen(name), name);
}

int typeFunctionGlobalTable(char *type){
	return (strcmp(type, "_function_") == 0) ? 1 : 0;
}

void printGlobalVariable(SymbolTableLine *symbolTableLine){
	printf("@%s = common global %s 0\n", symbolTableLine->name, varTypeTable(symbolTableLine->type));
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
	searchInMain(aux);
	
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

	aux = aux->brother;

	if(strcmp(aux->type, "FuncPart") == 0){
		aux = aux->brother;
	}

	return aux;
}

void searchInMain(Program *program){
	if(program != NULL){
		if(strcmp(program->type, "WriteLn") == 0){
			program = program->son;
			searchWriteLn(program);
		}

		searchInMain(program->son);
		searchInMain(program->brother);
	}
}

void searchWriteLn(Program *program){
	char temp[17];
	
	while(program != NULL){
		if(strcmp(program->type, "IntLit") == 0){
			printWriteLn(SIZE_INT, "@.strInt", program->value);
		}

		else if(strcmp(program->type, "RealLit") == 0){
			printWriteLn(SIZE_INT, "@.strDouble", program->value);
		}

		else if(strcmp(program->type, "String") == 0){
			sprintf(temp, "%d", findId(program->value));
			printWriteLn(SIZE_INT, temp, "0");
		}

		program = program->brother;
	}

	printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @.strNewLine, i32 0, i32 0))\n", index_string_name++);
}

void printWriteLn(int size, char *id, char *value){
	printf("  %%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([%d x i8]* %s, i32 0, i32 %s))\n", index_string_name++, size, id, value);
}

#endif
