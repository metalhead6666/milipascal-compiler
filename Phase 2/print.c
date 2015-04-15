#include "print.h"

int counter = 0;

void print_tree(Program* program){
	printf("Program\n");

	counter += 2;
	print_dots(counter);
	print_id(program->id);

	print_varPart(program->progBlock->varPart);
	counter -= 4;
	print_funcPart(program->progBlock->funcPart);
}

void print_varPart(VarPart* root){
	print_dots(counter);
	printf("VarPart\n");
	counter += 2;
	print_dots(counter);
	printf("VarDecl\n");
	counter += 2;

	while(root != NULL){		
		print_dots(counter);
		print_id(root->varDecl->first_id);

		while(root->varDecl->id != NULL){
			print_dots(counter);
			print_id(root->varDecl->id->id);

			root->varDecl->id = root->varDecl->id->next;
		}

		print_dots(counter);
		print_id(root->varDecl->last_id);

		root = root->next;
	}
}

void print_funcPart(FuncPart* funcPart){
	print_dots(counter);
	printf("FuncPart\n");

	if(funcPart != NULL){
		counter += 2;
		print_dots(counter);
		printf("FuncDecl\n");

		counter += 2;
		
		while(funcPart->next != NULL){
			print_dots(counter);
			print_id(funcPart->funcDeclaration->funcDeclarationUnion.id);
		}
	}
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
