#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

Program* makeNode(char* id, ProgBlock* progBlock);
ProgBlock* addProgBlock(VarPart* varPart, FuncPart* funcPart);

void print_tree(Program* program);

#endif
