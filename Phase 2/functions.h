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

#endif
