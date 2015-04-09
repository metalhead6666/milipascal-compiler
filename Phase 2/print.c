#include "print.h"

void print_tree(Program* program){
	int counter = 0;
	
	printf("Program\n");

	counter += 2;
	print_dots(counter);
	print_id(program->id);

	VarPart *root = program->progBlock->varPart;

	print_dots(counter);
	printf("VarPart\n");
	counter += 2;
	print_dots(counter);
	printf("VarDecl\n");
	counter += 2;

	while(root != NULL){		
		print_dots(counter);
		printf("Id(%s)\n", root->varDecl->first_id);

		while(root->varDecl->id != NULL){
			print_dots(counter);
			printf("Id(%s)\n", root->varDecl->id->id);

			root->varDecl->id = root->varDecl->id->next;
		}

		print_dots(counter);
		printf("Id(%s)\n", root->varDecl->last_id);

		root = root->next;
	}

	counter -= 4;
	print_dots(counter);
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
