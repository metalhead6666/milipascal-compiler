#include "functions.h"

/*
*	IdStruct
*	VarParams
*	Params
*	VarDecl
*	VarPart
*	ProgBlock
*	Program
*	FuncParams
*		|FuncParams_Params
*		|FuncParams_VarParams
*	FuncDecl
*	FuncDef
* 	FuncDef2
*	FuncPart
*		|FuncPart_FuncDecl
*		|FuncPart_FuncDef
*		|FuncPart_FuncDef2
*/

Program *makeNode(char* id, ProgBlock* progBlock){
	Program* prog = (Program *)malloc(sizeof(Program));
	prog->progBlock = progBlock;
	prog->id = id;

	return prog;
}

ProgBlock *addProgBlock(VarPart* varPart, FuncPart* funcPart){
	ProgBlock* progBlock = (ProgBlock *)malloc(sizeof(ProgBlock));
	progBlock->varPart = varPart;
	progBlock->funcPart = funcPart;

	return progBlock;
}

VarPart *addVarPart(VarPart *varPart, VarDecl *varDecl){
	VarPart *new_varPart = (VarPart *)malloc(sizeof(VarPart));
	new_varPart->varDecl = varDecl;
	new_varPart->next = varPart;

	return new_varPart;
}

VarDecl *addVarDecl(char *first_id, char *last_id, IdStruct *id){
	VarDecl *varDecl = (VarDecl *)malloc(sizeof(VarDecl));
	varDecl->first_id = first_id;
	varDecl->last_id = last_id;
	varDecl-> id = id;

	return varDecl;
}

IdStruct *addIdStruct(IdStruct* next, char *id){
	IdStruct *idStruct = (IdStruct *)malloc(sizeof(IdStruct));
	idStruct->next = next;
	idStruct->id = id;

	return idStruct;
}
