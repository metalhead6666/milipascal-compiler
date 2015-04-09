#include "print.h"

int counter = 0;

void print_tree(Program* program){
	printf("Program\n");

	counter += 2;
	print_dots(counter);

	print_id(program->id);
}

void print_id(char *id){
	printf("Id(%s)\n", id);
}

void print_dots(int counter){
	int i;

	for(i = 0; i < counter; ++i){
		printf(".");
	}
}
