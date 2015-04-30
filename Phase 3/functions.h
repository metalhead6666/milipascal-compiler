#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	Program* program = (Program *)calloc(1, sizeof(Program));
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

	if(aux != NULL && aux->brother != NULL){
		counter = 2;
	}

	return counter;
}

void print_tree(Program *program, int counter){
	if(program != NULL){
		if(strcmp(program->type,"NoPrint")==0){
			print_tree(program->son, counter + 2);
			print_tree(program->brother, counter);
			return;
		}

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

char* verify_Expr(char *expr){
	if(strcmp(expr,"=") == 0)
		return "Eq";
	if(strcmp(expr,">") == 0)
		return "Gt";
	if(strcmp(expr,"<") == 0)
		return "Lt";
	if(strcmp(expr,"<>") == 0)
		return "Neq";
	if(strcmp(expr,"<=") == 0)
		return "Leq";
	if(strcmp(expr,">=") == 0)
		return "Geq";
	return "";
}

char* verify_SimpleExpr(char *expr, int type){

	if(type==0){
		if(strcmp(expr,"+") == 0)
			return "Plus";
		if(strcmp(expr,"-") == 0)
			return "Minus";
	}

	if(type==1){
		if(strcmp(expr,"+") == 0)
			return "Add";
		if(strcmp(expr,"-") == 0)
			return "Sub";
	}
	return "Or";
}

char* verify_MultOp(char *term){
	if(term[0] == 'd' || term[0] == 'D')
		return "Div";
	if(term[0] == 'm' || term[0] == 'M')
		return "Mod";
	if(strcmp(term,"/")==0)
		return "RealDiv";
	if(strcmp(term,"*")==0)
		return "Mul";
	return "And";
}

#endif
