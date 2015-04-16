#include "print.h"

int counter = 0;

void print_tree(Program* program){
	printf("Program\n");

	counter += 2;
	print_dots(counter);
	print_id(program->id);

	print_varPart(program->progBlock->varPart);
	print_funcPart(program->progBlock->funcPart);
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

		print_IdStruct(varPart->varDecl->id);

		print_dots(counter);
		print_id(varPart->varDecl->last_id);

		varPart = varPart->next;
		
		counter -= 2;	
	}

	counter -= 2;
}

void print_IdStruct(IdStruct* id){
	while(id != NULL){
		print_dots(counter);
		print_id(id->id);

		id = id->next;
	}
}

void print_funcPart(FuncPart* funcPart){
	FuncHeading *funcHeading;

	print_dots(counter);
	printf("FuncPart\n");

	while(funcPart != NULL){
		counter += 2;
		print_dots(counter);
		printf("FuncDecl\n");		
		
		counter += 2;
		print_dots(counter);
		
		if(funcPart->funcDeclaration->type == 1){
			funcHeading = funcPart->funcDeclaration->funcDeclarationUnion.funcHeading;
			
			print_id(funcHeading->first_id);
			counter += 2;			

			while(funcHeading->next != NULL && funcHeading->next->formalParams != NULL){
				print_dots(counter);
				print_id(funcHeading->next->formalParams->first_id);

				print_IdStruct(funcHeading->next->formalParams->idStruct);
				
				print_dots(counter);			
				print_id(funcHeading->next->formalParams->last_id);
				
				funcHeading->next = funcHeading->next->next;
			}

			counter -= 2;
			print_dots(counter);
			print_id(funcHeading->last_id);
		}

		else{
			print_id(funcPart->funcDeclaration->funcDeclarationUnion.id);
		}

		counter -= 2;
		print_varPart(funcPart->funcDeclaration->varPart);
		print_statList(funcPart->funcDeclaration->stat);
		funcPart = funcPart->next;
		counter -= 2;
	}
}

void print_statList(Stat *stat){
	print_dots(counter);
	printf("StatList\n");

	/*while(stat != NULL){
		stat = stat->next;
	}*/
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
