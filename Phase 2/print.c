#include "print.h"

int counter = 0;

void print_tree(Program* program){
	printf("Program\n");

	counter += 2;
	print_dots(counter);
	print_id(program->id);

	print_varPart(program->progBlock->varPart);
	counter -= 2;
	print_funcPart(program->progBlock->funcPart);
	//counter -= 2;
	print_statList(program->progBlock->stat);
}

void print_varPart(VarPart* varPart){
	print_dots(counter);
	printf("VarPart\n");
	counter += 2;	

	while(varPart != NULL){
		print_dots(counter);
		printf("VarDecl\n");
		counter += 2;
		
		print_dots(counter);
		print_id(varPart->varDecl->first_id);

		while(varPart->varDecl->id != NULL){
			print_dots(counter);
			print_id(varPart->varDecl->id->id);

			varPart->varDecl->id = varPart->varDecl->id->next;
		}

		print_dots(counter);
		print_id(varPart->varDecl->last_id);

		varPart = varPart->next;
		
		counter -= 2;	
	}
}

void print_funcPart(FuncPart* funcPart){
	print_dots(counter);
	printf("FuncPart\n");

	if(funcPart != NULL){
		counter += 2;
		print_dots(counter);
		printf("FuncDecl\n");		
		
		while(funcPart != NULL){
			counter += 2;
			print_dots(counter);
			print_id(funcPart->funcDeclaration->funcDeclarationUnion.id);

			counter -= 2;
			print_varPart(funcPart->funcDeclaration->varPart);
			funcPart = funcPart->next;
		}
	}
}

void print_statList(Stat *stat){
	print_dots(counter);
	printf("StatList\n");

	while(stat != NULL){

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
