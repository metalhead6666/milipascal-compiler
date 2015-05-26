#ifndef _GENERATOR_
#define _GENERATOR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

/*Functions*/
void generateProgram(Program* program);
void generateFunctions(char* type, char* name, Program *program);
char *varType(char *type);


void generateProgram(Program* program){

	generateFunctions(program->value, "main", program);

	if(program != NULL){	
		generateProgram(program->son);
		generateProgram(program->brother);
	}
}

void generateFunctions(char* type, char* name, Program *program){
	printf("define %s @%s(", varType(type), name);
	while(){
		
	}
}

char *varType(char *type){
	if(strcmp(type, "integer") == 0)
		return "i32";

	if(strcmp(type, "boolean") == 0)
		return "i1";

	if(strcmp(type, "real") == 0)
		return "double";

	return NULL;
}

#endif
