#ifndef _PRINT_
#define _PRINT_

#include <stdio.h>
#include "structures.h"

int count_nodes(StatList *statList);
void print_tree(Program* program);
void print_varPart(VarPart* varPart, int counter);
void print_IdStruct(IdStruct* id, int counter);
void print_funcPart(FuncPart* funcPart, int counter);
void print_statList(StatList *statList, int counter);
void print_statements(Stat *stat, int counter);
void print_Expr(Expr *expr, int counter);
void print_SimpleExpr(SimpleExpr *simpleExpr, int counter);
void print_term(Term *term, int counter);
void print_factor(Factor *factor, int counter);
void print_WriteInPList(WriteInPList *writeInPList, int counter);
void print_dots(int counter);
void print_id(char *id);

#endif 
