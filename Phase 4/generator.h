#ifndef _GENERATOR_
#define _GENERATOR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "semantic.h"


/*Functions*/
void generateProgram(Program* program, SymbolTableHeader *symbolTableHeader);
int typeFunctionGlobalTable(char *type);
void printGlobalVariable(SymbolTableLine *symbolTableLine);
void createHeaderFunction(char* name, Program *program, SymbolTableHeader *symbolTableHeader);
SymbolTableHeader *findTableFunction(char* name, SymbolTableHeader *symbolTableHeader);
void printHeaderFunction(char *type, char *name);
SymbolTableLine *findParamFunction(SymbolTableLine *symbolTableLine);
void findVarFunction(SymbolTableLine *symbolTableLine);
void printVarFunction(char *name, char *type);
void printReturnFunction(char *type, char *name);
char *varType(char *type);


void generateProgram(Program* program, SymbolTableHeader *symbolTableHeader){
	while(symbolTableHeader->symbolTableLine != NULL){
		if(typeFunctionGlobalTable(symbolTableHeader->symbolTableLine->type)){
			createHeaderFunction(symbolTableHeader->symbolTableLine->name, program, symbolTableHeader);			
		}

		else{
			printGlobalVariable(symbolTableHeader->symbolTableLine);
		}

		symbolTableHeader->symbolTableLine = symbolTableHeader->symbolTableLine->next;
	}

	/* 
	if(program != NULL){
		if(strcmp(program->type, "FuncDef") == 0){
			createHeaderFunction(program->son->value, program->son, symbolTableHeader);
		}

		generateProgram(program->son, symbolTableHeader);
		generateProgram(program->brother, symbolTableHeader);
	}
	*/
}

int typeFunctionGlobalTable(char *type){
	return (strcmp(type, "_function_") == 0) ? 1 : 0;
}

void printGlobalVariable(SymbolTableLine *symbolTableLine){
	printf("@%s = common global %s 0\n", symbolTableLine->name, varType(symbolTableLine->type));
}

void createHeaderFunction(char *name, Program *program, SymbolTableHeader *symbolTableHeader){
	SymbolTableHeader *table;
	SymbolTableLine *temp;

	table = findTableFunction(name, symbolTableHeader->next);
	
	printHeaderFunction(varType(table->symbolTableLine->type), table->symbolTableLine->name);
	
	temp = findParamFunction(table->symbolTableLine->next);
	printf(") {\n");
	findVarFunction(temp);
	
	printReturnFunction(varType(table->symbolTableLine->type), "0");
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
	while(1){
		printf("%s %%%s", varType(symbolTableLine->type), symbolTableLine->name);

		symbolTableLine = symbolTableLine->next;

		if(symbolTableLine != NULL && symbolTableLine->flag != NULL){
			printf(", ");
		}

		else{
			break;
		}
	}

	return symbolTableLine;
}

void findVarFunction(SymbolTableLine *symbolTableLine){
	while(symbolTableLine != NULL){
		printVarFunction(symbolTableLine->name, varType(symbolTableLine->type));

		symbolTableLine = symbolTableLine->next;
	}
}

void printVarFunction(char *name, char *type){
	printf("  @%s = local %s 0\n", name, type);
}

void printReturnFunction(char *type, char *name){
	printf("  ret %s %s\n}\n", type, name);
}

char *varType(char *type){
	if(strcmp(type, "_integer_") == 0){
		return "i32";
	}

	if(strcmp(type, "_boolean_") == 0){
		return "i1";
	}

	if(strcmp(type, "_real_") == 0){
		return "double";
	}

	return NULL;
}

#endif
