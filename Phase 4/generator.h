#ifndef _GENERATOR_
#define _GENERATOR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "semantic.h"


/*Functions*/
void generateProgram(Program* program, SymbolTableHeader *symbolTableHeader);
void createHeaderFunction(char* name, Program *program, SymbolTableHeader *symbolTableHeader);
SymbolTableHeader *findTableFunction(char* name, SymbolTableHeader *symbolTableHeader);
char *varType(char *type);


void generateProgram(Program* program, SymbolTableHeader *symbolTableHeader){

	if(program != NULL){
		if(strcmp(program->type, "FuncDef")==0){
			createHeaderFunction(program->son->value, program->son, symbolTableHeader);
		}

		generateProgram(program->son,symbolTableHeader);
		generateProgram(program->brother,symbolTableHeader);
	}
}

void createHeaderFunction(char* name, Program *program, SymbolTableHeader *symbolTableHeader){
	SymbolTableHeader *table;
	table = findTableFunction(name, symbolTableHeader->next);
	printf("define %s @%s(", varType(table->symbolTableLine->type), table->symbolTableLine->name);
}

SymbolTableHeader *findTableFunction(char* name, SymbolTableHeader *symbolTableHeader){
	SymbolTableLine *line;
	while(symbolTableHeader!=NULL){	
		line = symbolTableHeader->symbolTableLine;
		if(strcmp(to_lower_case(name), line->name)==0){
			return symbolTableHeader;
		}		
		symbolTableHeader = symbolTableHeader->next;
	}
	return NULL;
}

char *varType(char *type){
	if(strcmp(type, "_integer_") == 0)
		return "i32";

	if(strcmp(type, "_boolean_") == 0)
		return "i1";

	if(strcmp(type, "_real_") == 0)
		return "double";

	return NULL;
}

#endif
