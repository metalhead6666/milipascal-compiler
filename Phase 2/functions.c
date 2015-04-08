#include "functions.h"

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


