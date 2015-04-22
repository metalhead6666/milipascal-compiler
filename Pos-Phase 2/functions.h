#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>

typedef struct Program Program;
struct Program{
	char* type;
	char* value;
	Program *son;
	Program *brother;
};


Program *makeNode(char *type, char *value, Program *son, Program *brother);
void print_tree(Program *program, int counter);
void print_dots(int counter);
int verify_terminal(char *type);


Program *makeNode(char *type, char *value, Program *son, Program *brother){
	Program* program = (Program *)malloc(sizeof(Program));
	program->type = type;
	program->value = value;
	program->son = son;
	program->brother = brother;

	return program;
}

Program *insert_last_brother(Program *program){
	Program *aux = program; 

	if(program == NULL){
		return NULL;
	}

	while(aux->brother != NULL){
		aux = aux->brother; 
	}

	return aux;
}

int count_nodes(Program *program){
	Program *aux = program;
	int counter = 0;

	while(aux != NULL){
		aux = aux->brother;
	}

	return counter;
}

void print_tree(Program *program, int counter){
	if(program != NULL){
		print_dots(counter);

		if(verify_terminal(program->type)){
			printf("%s(%s)\n", program->type, program->value);
		}

		else{
			printf("%s\n", program->type);
		}

		print_tree(program->son, counter + 2);
		print_tree(program->brother, counter);
	}
}

void print_dots(int counter){
	int i;

	for(i = 0; i < counter; ++i){
		printf(".");
	}
}

int verify_terminal(char *type){
	if(strcmp(type, "Id") == 0 || 
	   strcmp(type, "RealLit") == 0 ||
	   strcmp(type, "IntLit") == 0 ||
	   strcmp(type, "String") == 0){

		return 1;
	}

	return 0;
}

#endif
