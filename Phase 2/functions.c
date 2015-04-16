#include "functions.h"

Program *makeNode(char* id, ProgBlock* progBlock){
	Program* prog = (Program *)malloc(sizeof(Program));
	prog->progBlock = progBlock;
	prog->id = id;

	return prog;
}

ProgBlock *addProgBlock(VarPart* varPart, FuncPart* funcPart, StatList *stat){
	ProgBlock* progBlock = (ProgBlock *)malloc(sizeof(ProgBlock));
	progBlock->varPart = varPart;
	progBlock->funcPart = funcPart;
	progBlock->stat = stat;

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

FuncDeclaration *addFuncDeclaration(VarPart *varPart, char* id, FuncHeading *funcHeading, int type, StatList *stat){
	FuncDeclaration *funcDeclaration = (FuncDeclaration *)malloc(sizeof(FuncDeclaration));
	funcDeclaration->varPart=varPart;
	funcDeclaration->type = type;
	funcDeclaration->stat = stat;

	if(type == 1){			
		funcDeclaration->funcDeclarationUnion.funcHeading=funcHeading;
	}

	else{
		funcDeclaration->funcDeclarationUnion.id=id;
	}

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

StatList *addStatList(Stat *stat, StatList *next){
	StatList *statList = (StatList *)malloc(sizeof(StatList));
	statList->stat = stat;
	statList->next = next;

	return statList;
}

Stat *addStat(Expr *expr, Stat *next, WriteInPList *writeInPList, char *id, StatList * statList, int type){
	Stat *stat = (Stat *)malloc(sizeof(Stat));
	stat->expr = expr;
	stat->next = next;
	stat->writeInPList = writeInPList;
	stat->type = type;

	if(type==1){
		stat->StatUnion.id = id;
	}
	else if(type==2){
		stat->StatUnion.statList = statList;
	}

	return stat;
}

WriteInPList *addWriteInPList(Optional *optional, WriteInPList *next){
	WriteInPList *writeInPList = (WriteInPList *)malloc(sizeof(WriteInPList));
	writeInPList->optional = optional;
	writeInPList->next = next;

	return writeInPList;
}

Optional *addOptional(Expr *expr, char *string, int type){
	Optional *optional = (Optional *)malloc(sizeof(Optional));
	optional->type = type;

	if(type==1){
		optional->OptionalUnion.expr = expr;
	}
	else{
		optional->OptionalUnion.string = string;
	}

	return optional;
}

Expr *addExpr(SimpleExpr *first_simpleExpr, SimpleExpr *last_simpleExpr, char* relationalOp){
	Expr *expr = (Expr *)malloc(sizeof(Expr));
	expr->first_simpleExpr = first_simpleExpr;
	expr->last_simpleExpr = last_simpleExpr;
	expr->relationalOp = relationalOp;

	return expr;
}

SimpleExpr *addSimpleExpr(Term *term, char* addOp, SimpleExpr *next){
	SimpleExpr *simpleExpr = (SimpleExpr *)malloc(sizeof(SimpleExpr));
	simpleExpr->term = term;
	simpleExpr->addOp = addOp;
	simpleExpr->next = next;

	return simpleExpr;
}

Term *addTerm(Factor *factor, Term *next, char* multOp){
	Term *term = (Term *)malloc(sizeof(Term));
	term->factor = factor;
	term->next = next;
	term->multOp = multOp;

	return term;
}

Factor *addFactor(Expr *expr, char *tokenOp, ParamList *paramList, Factor *next){
	Factor *factor = (Factor *)malloc(sizeof(Factor));
	factor->expr = expr;
	factor->tokenOp = tokenOp;
	factor->paramList = paramList;
	factor->next = next;

	return factor;
}

ParamList *addParamList(Expr *expr, ParamList *next){
	ParamList *paramList = (ParamList *)malloc(sizeof(ParamList));
	paramList->expr = expr;
	paramList->next = next;

	return paramList;
}