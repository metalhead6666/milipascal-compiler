#include "functions.h"

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

FuncPart *addFuncPart(FuncPart* next, FuncDeclaration *funcDeclaration){
	FuncPart *new_funcPart = (FuncPart *)malloc(sizeof(FuncPart));
	new_funcPart->next = next;
	new_funcPart->funcDeclaration = funcDeclaration;

	return new_funcPart;
}

FuncDeclaration *addFuncDeclaration(VarPart *varPart, char* id, FuncHeading *funcHeading){
	FuncDeclaration *funcDeclaration = (FuncDeclaration *)malloc(sizeof(FuncDeclaration));
	funcDeclaration->varPart=varPart;
	funcDeclaration->funcDeclarationUnion.id=id;
	funcDeclaration->funcDeclarationUnion.funcHeading=funcHeading;

	return funcDeclaration;
}

FuncHeading *addFuncHeading(char* first_id, FormalParamList *next, char* last_id){
	FuncHeading *funcHeading = (FuncHeading *)malloc(sizeof(FuncHeading));
	funcHeading->first_id = first_id;
	funcHeading->next = next;
	funcHeading->last_id = last_id;

	return funcHeading;
}

FormalParamList *addFormalParamList(FormalParams *formalParams, FormalParamList *next){
	FormalParamList *formalParamList = (FormalParamList *)malloc(sizeof(FormalParamList));
	formalParamList->formalParams = formalParams;
	formalParamList->next = next;

	return formalParamList;
}

FormalParams *addFormalParams(char* first_id, IdStruct *idStruct, char* last_id){
	FormalParams *formalParams = (FormalParams *)malloc(sizeof(FormalParams));
	formalParams->first_id = first_id;
	formalParams->idStruct = idStruct;
	formalParams->last_id = last_id;

	return formalParams;
}