#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <stdlib.h>
#include "structures.h"

Program* makeNode(char* id, ProgBlock* progBlock);
ProgBlock* addProgBlock(VarPart* varPart, FuncPart* funcPart, StatList *stat);
VarPart *addVarPart(VarPart *varPart, VarDecl *varDecl);
VarDecl *addVarDecl(char *first_id, char *last_id, IdStruct *id);
IdStruct *addIdStruct(IdStruct* next, char *id);
FuncPart *addFuncPart(FuncPart* next, FuncDeclaration *funcDeclaration);
FuncDeclaration *addFuncDeclaration(VarPart *varPart, char* id, FuncHeading *funcHeading, int type, StatList *stat);
FuncHeading *addFuncHeading(char* first_id, FormalParamList *next, char* last_id);
FormalParamList *addFormalParamList(FormalParams *formalParams, FormalParamList *next);
FormalParams *addFormalParams(char* first_id, IdStruct *idStruct, char* last_id);
StatList *addStatList(Stat *stat, StatList *next);
Stat *addStat(Expr *expr, Stat *next, WriteInPList *writeInPList, char *id, StatList * statList, int type, Statements statement);
WriteInPList *addWriteInPList(Optional *optional, WriteInPList *next);
Optional *addOptional(Expr *expr, char *string, int type);
Expr *addExpr(SimpleExpr *first_simpleExpr, SimpleExpr *last_simpleExpr, char* relationalOp);
SimpleExpr *addSimpleExpr(Term *term, char* addOp, SimpleExpr *next, int type);
Term *addTerm(Factor *factor, Term *next, char* multOp);
Factor *addFactor(Expr *expr, char *tokenOp, ParamList *paramList, Factor *factor, Terminals terminal);
ParamList *addParamList(Expr *expr, ParamList *next);

#endif
