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

IdStruct *addIdStruct(IdStruct* next, char *id){
	IdStruct *idStruct = (IdStruct *)malloc(sizeof(IdStruct));
	idStruct->next = next;
	idStruct->id = id;

	return idStruct;
}

VarParams *addVarParams(char *first_id, char *last_id, IdStruct *id){
	VarParams *varParams = (VarParams *)malloc(sizeof(VarParams));
	varParams->first_id = first_id;
	varParams->last_id = last_id;
	varParams-> id = id;

	return varParams;
}

Params *addParams(char *first_id, char *last_id, IdStruct *id){
	Params *params = (Params *)malloc(sizeof(Params));
	params->first_id = first_id;
	params->last_id = last_id;
	params-> id = id;

	return params;
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

FuncParams *addFuncParams_Params(Params *params){
	FuncParams *funcParams = (FuncParams *)malloc(sizeof(FuncParams));
	funcParams->OptionalParams.params = params;

	return funcParams;
}

FuncParams *addFuncParams_VarParams(VarParams *varParams){
	FuncParams *funcParams = (FuncParams *)malloc(sizeof(FuncParams));
	funcParams->OptionalParams.varParams = varParams;

	return funcParams;
}

FuncDecl *addFuncDecl(char *first_id, char *last_id, FuncParams *funcParams){
	FuncDecl *funcDecl = (FuncDecl *)malloc(sizeof(FuncDecl));
	funcDecl->first_id = first_id;
	funcDecl->last_id = last_id;
	funcDecl-> funcParams = funcParams;

	return funcDecl;
}

FuncDef *addFuncDef(FuncDecl *funcDecl, VarPart *varPart, Statements stat){
	FuncDef *funcDef = (FuncDef *)malloc(sizeof(FuncDef));
	funcDef->funcDecl = funcDecl;
	funcDef->varPart = varPart;
	funcDef->stat = stat;

	return funcDef;
}

FuncDef2 *addFuncDef2(char *id, VarPart *varPart, Statements stat){
	FuncDef2 *funcDef = (FuncDef2 *)malloc(sizeof(FuncDef2));
	funcDef->id = id;
	funcDef->varPart = varPart;
	funcDef->stat = stat;

	return funcDef;
}

FuncPart *addFuncPart_FuncDecl(FuncPart *next, FuncDecl *funcDecl){
	FuncPart *funcPart = (FuncPart *)malloc(sizeof(FuncPart));
	funcPart->next = next;
	funcPart->funcPart.funcDecl = funcDecl;

	return funcPart;
}

FuncPart *addFuncPart_FuncDef(FuncPart *next, FuncDef *funcDef){
	FuncPart *funcPart = (FuncPart *)malloc(sizeof(FuncPart));
	funcPart->next = next;
	funcPart->funcPart.funcDef = funcDef;

	return funcPart;
}

FuncPart *addFuncPart_FuncDef2(FuncPart *next, FuncDef2 *funcDef2){
	FuncPart *funcPart = (FuncPart *)malloc(sizeof(FuncPart));
	funcPart->next = next;
	funcPart->funcPart.funcDef2 = funcDef2;

	return funcPart;
}
