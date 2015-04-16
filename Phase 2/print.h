#ifndef _PRINT_
#define _PRINT_

#include <stdio.h>
#include "structures.h"

void print_tree(Program* program);
void print_varPart(VarPart* varPart);
void print_IdStruct(IdStruct* id);
void print_funcPart(FuncPart* funcPart);
void print_statList(StatList *stat);
void print_dots(int counter);
void print_id(char *id);

#endif 
