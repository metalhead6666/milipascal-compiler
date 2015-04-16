#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <stdlib.h>
#include "structures.h"

Program* makeNode(char* id, ProgBlock* progBlock);
ProgBlock* addProgBlock(VarPart* varPart, FuncPart* funcPart);
VarPart *addVarPart(VarPart *varPart, VarDecl *varDecl);
VarDecl *addVarDecl(char *first_id, char *last_id, IdStruct *id);
IdStruct *addIdStruct(IdStruct* next, char *id);
FuncPart *addFuncPart(FuncPart* next, FuncDeclaration *funcDeclaration);
FuncDeclaration *addFuncDeclaration(VarPart *varPart, char* id, FuncHeading *funcHeading);
FuncHeading *addFuncHeading(char* first_id, FormalParamList *next, char* last_id);
FormalParamList *addFormalParamList(FormalParams *formalParams, FormalParamList *next);
FormalParams *addFormalParams(char* first_id, IdStruct *idStruct, char* last_id);
StatList *addStatList(Stat *stat, StatList *next);
Stat *addStat(Expr *expr, Stat *next, WriteInPList *writeInPList, char *id, StatList * statList);
WriteInPList *addWriteInPList(Expr *expr, WriteInPList *next);
Optional *addOptional(Expr *expr, char *string);

#endif
