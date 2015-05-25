#ifndef _GENERATOR_
#define _GENERATOR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void generateProgram(Program* program){
	if(program != NULL){
		if(strcmp(program->type,"WriteLn")==0){
			printf("WriteLn\n");
		}


		generateProgram(program->son);
		generateProgram(program->brother);
	}
}

#endif
