#include "functions.h"

int counter=0;

Program* makeNode(char* id, ProgBlock* progBlock){
	Program* prog = (Program *)malloc(sizeof(Program));
	prog->progBlock = progBlock;
	prog->id = id;

	return prog;
}

ProgBlock* addProgBlock(VarPart* varPart, FuncPart* funcPart){
	ProgBlock* progBlock = (ProgBlock *)malloc(sizeof(ProgBlock));
	progBlock->varPart = varPart;
	progBlock->funcPart = funcPart;

	return progBlock;
}

void print_tree(Program* program){
	printf("Program\n");
	counter+=2;
	print_dots(counter);
	printf("Id(%s)\n", program->id);
}

void print_dots(int counter){
	int i;
	for(i=0;i<counter;i++){
		printf(".");
	}
}
