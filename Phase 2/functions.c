#include "functions.h"

Program* makeNode(char* id){
	Program* prog = (Program *)malloc(sizeof(Program));
	//prog->progBlock = progBlock;
	strcpy(prog->id, id);

	return prog;
}

ProgBlock* addProgBlock(VarPart* varPart, FuncPart* funcPart){
	ProgBlock* progBlock = (ProgBlock *)malloc(sizeof(ProgBlock));
	progBlock->varPart = varPart;
	progBlock->funcPart = funcPart;

	return progBlock;
}

void print_tree(Program* program){
	printf("%s\n", program->id);
}
