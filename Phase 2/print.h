#ifndef _PRINT_
#define _PRINT_

#include <stdio.h>
#include "structures.h"

void print_tree(Program* program);
void print_varPart(VarPart* varPart);
void print_IdStruct(IdStruct* id);
void print_funcPart(FuncPart* funcPart);
void print_statList(StatList *statList);
void print_Expr(Expr *expr);
void print_WriteInPList(WriteInPList *writeInPList);
void print_dots();
void print_id(char *id);

#endif 
