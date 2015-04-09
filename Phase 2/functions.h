#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <stdlib.h>
#include "structures.h"

Program* makeNode(char* id, ProgBlock* progBlock);
ProgBlock* addProgBlock(VarPart* varPart, FuncPart* funcPart);
VarPart *addVarPart(VarPart *varPart, VarDecl *varDecl);
VarDecl *addVarDecl(char *first_id, char *last_id, IdStruct *id);
IdStruct *addIdStruct(IdStruct* next, char *id);
VarParams *addVarParams(char *first_id, char *last_id, IdStruct *id);
Params *addParams(char *first_id, char *last_id, IdStruct *id);
FuncParams *addFuncParams_Params(Params *params);
FuncParams *addFuncParams_VarParams(VarParams *varParams);
FuncDecl *addFuncDecl(char *first_id, char *last_id, FuncParams *funcParams);
FuncDef *addFuncDef(FuncDecl *funcDecl, VarPart *varPart, Statements stat);
FuncDef2 *addFuncDef2(char *id, VarPart *varPart, Statements stat);
FuncPart *addFuncPart_FuncDecl(FuncPart *next, FuncDecl *funcDecl);
FuncPart *addFuncPart_FuncDef(FuncPart *next, FuncDef *funcDef);
FuncPart *addFuncPart_FuncDef2(FuncPart *next, FuncDef2 *funcDef2);

#endif
