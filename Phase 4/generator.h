#ifndef _GENERATOR_
#define _GENERATOR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void generateProgram(Program* program){
	if(program!=NULL){
		if(strcmp(program->type, "NoPrint") == 0){
			generateProgram(program->son);
			generateProgram(program->brother);
			return;
		}

		if(verify_terminal(program->type)){
			printf("%s(%s)\n", program->type, program->value);
		}

		else{
			printf("%s\n", program->type);
		}

		generateProgram(program->son);
		generateProgram(program->brother);
	}
}

#endif