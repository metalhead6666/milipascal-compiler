#include "print.h"

int aux_counter = 2;

void print_tree(Program* program){
	int counter = 2;
	printf("Program\n");

	print_dots(counter);
	print_id(program->id);

	print_dots(counter);
	printf("VarPart\n");

	print_varPart(program->progBlock->varPart, counter);

	print_dots(counter);
    printf("FuncPart\n");

	print_funcPart(program->progBlock->funcPart, counter);

	print_dots(counter);
	printf("StatList\n");

	print_statList(program->progBlock->stat, counter);
}

void print_varPart(VarPart* varPart, int counter){
	counter += 2;
		
	while(varPart != NULL){
		print_dots(counter);
		printf("VarDecl\n");
		
		counter += 2;
		print_dots(counter);
		print_id(varPart->varDecl->first_id);

		print_IdStruct(varPart->varDecl->id, counter);

		print_dots(counter);
		print_id(varPart->varDecl->last_id);

		varPart = varPart->next;
		counter -= 2;
	}
}

void print_IdStruct(IdStruct* id, int counter){
	while(id != NULL){
		print_dots(counter);
		print_id(id->id);

		id = id->next;
	}
}

void print_funcPart(FuncPart* funcPart, int counter){
    FuncHeading *funcHeading;
    int temp;

    counter += 2;

    while(funcPart != NULL){
    	temp = 0;

        if(funcPart->funcDeclaration->type == 1){
            funcHeading = funcPart->funcDeclaration->funcDeclarationUnion.funcHeading;
            print_dots(counter);

            if(funcPart->funcDeclaration->varPart == NULL && funcPart->funcDeclaration->stat == NULL){
            	temp = 0;
                printf("FuncDecl\n");
            }

            else{
            	temp = 1;
                printf("FuncDef\n");
            }
           
            counter += 2;
            print_dots(counter);
            print_id(funcHeading->first_id);

            print_dots(counter);
            printf("FuncParams\n");
            counter += 2;

            while(funcHeading->next != NULL && funcHeading->next->formalParams != NULL){
                print_dots(counter);

                if(funcHeading->next->formalParams->type == 1){                                
                    printf("VarParams\n");
                }

                else{                                  
                    printf("Params\n");
                }

                counter += 2;
                print_dots(counter);
                print_id(funcHeading->next->formalParams->first_id);

                print_IdStruct(funcHeading->next->formalParams->idStruct, counter);
               
                print_dots(counter);                   
                print_id(funcHeading->next->formalParams->last_id);
               
                funcHeading->next = funcHeading->next->next;
                counter -= 2;
            }

            counter -= 2;                  
            print_dots(counter);
            print_id(funcHeading->last_id);

            if(temp == 1){
                print_dots(counter);
                printf("VarPart\n");
            }

            print_varPart(funcPart->funcDeclaration->varPart, counter);

            if(temp == 1){
                print_dots(counter);
                printf("StatList\n");
            }

            print_statList(funcPart->funcDeclaration->stat, counter);
            counter -= 2;
        }

        else{
            print_dots(counter);
            printf("FuncDef2\n");

            print_dots(counter + 2);
            print_id(funcPart->funcDeclaration->funcDeclarationUnion.id);

            print_dots(counter + 2);
            printf("VarPart\n");

            print_varPart(funcPart->funcDeclaration->varPart, counter + 2);
           
            print_dots(counter + 2);
            printf("StatList\n");
           
            print_statList(funcPart->funcDeclaration->stat, counter + 2);
        }
                       
        funcPart = funcPart->next;     
    }	
}

void print_statList(StatList *statList, int counter){
	while(statList != NULL){
		while(statList->stat != NULL){
			printStatements(statList->stat, counter + aux_counter);
			statList->stat = statList->stat->next;
		}

		statList = statList->next;
	}
}

void printStatements(Stat *stat, int counter){
	print_dots(counter);

	switch(stat->statement){
	case Assign:				
		printf("Assign\n");
		print_dots(counter + 2);
		print_id(stat->StatUnion.id);
		print_Expr(stat->expr, counter + 2);
		break;

	case IfElse:
		printf("IfElse\n");		
		print_Expr(stat->expr, counter + 2);
		
		if(stat->next != NULL){
			aux_counter += 2;
		}

		else{
			aux_counter -= 2;
		}

		break;

	case Repeat:
		printf("Repeat\n");
		print_statList(stat->StatUnion.statList, counter);
		print_Expr(stat->expr, counter + 2);		
		break;

	case StatList1:
		printf("StatList\n");
		print_statList(stat->StatUnion.statList, counter-aux_counter);		
		break;

	case ValParam:
		printf("ValParam\n");
		print_Expr(stat->expr, counter + 2);
		print_dots(counter + 2);
		print_id(stat->StatUnion.id);
		break;

	case While:
		printf("While\n");		
		print_Expr(stat->expr, counter + 2);
		//printStatements(stat->next, counter + 2);
		break;

	case WriteLn:
		printf("WriteLn\n");
		print_WriteInPList(stat->writeInPList, counter + 2);
		break;
	}
}

void print_Expr(Expr *expr, int counter){
	if(expr != NULL){
		if(expr->relationalOp != NULL){
			print_dots(counter);

			if(strcmp(expr->relationalOp, "<") == 0){
				printf("Lt\n");
			}

			else if(strcmp(expr->relationalOp, ">") == 0){
				printf("Gt\n");
			}

			else if(strcmp(expr->relationalOp, "=") == 0){
				printf("Eq\n");
			}

			else if(strcmp(expr->relationalOp, "<>") == 0){
				printf("Neq\n");
			}

			else if(strcmp(expr->relationalOp, "<=") == 0){
				printf("Leq\n");
			}

			else if(strcmp(expr->relationalOp, ">=") == 0){
				printf("Geq\n");
			}

			counter += 2;
		}
		
		print_SimpleExpr(expr->first_simpleExpr, counter);
		print_SimpleExpr(expr->last_simpleExpr, counter);
	}
}

void print_SimpleExpr(SimpleExpr *simpleExpr, int counter){
	while(simpleExpr != NULL){		
		if(simpleExpr->type == 1){
			print_dots(counter);			
			
			if(strcmp(simpleExpr->addOp, "+") == 0){
				printf("Plus\n");
			}

			else{
				printf("Minus\n");
			}

			counter += 2;
		}

		else if(simpleExpr->type == 2){
			print_dots(counter);

			if(strcmp(simpleExpr->addOp, "+") == 0){
				printf("Add\n");
			}

			else if(strcmp(simpleExpr->addOp, "-") == 0){
				printf("Sub\n");
			}

			else{
				printf("Or\n");
			}

			counter += 2;
		}
		
		print_term(simpleExpr->term, counter);
		simpleExpr = simpleExpr->next;
	}
}

void print_term(Term *term, int counter){
	while(term != NULL){
		if(term->multOp != NULL){
			print_dots(counter);

			if(strcmp(term->multOp, "and") == 0){
				printf("And\n");
			}

			else if(strcmp(term->multOp, "mod") == 0){
				printf("Mod\n");
			}

			else if(strcmp(term->multOp, "div") == 0){
				printf("Div\n");
			}

			else if(strcmp(term->multOp, "*") == 0){
				printf("Mul\n");
			}

			else if(strcmp(term->multOp, "/") == 0){
				printf("RealDiv\n");
			}

			counter += 2;
		}

		print_factor(term->factor, counter);
		term = term->next;
	}
}

void print_factor(Factor *factor, int counter){
	if(factor->expr != NULL){
		print_Expr(factor->expr, counter + 2);
	}
	
	switch(factor->terminal){
	case Not:
		print_dots(counter);
		printf("Not\n");
		print_factor(factor->next, counter + 2);
		break;

	case IntLit:
		print_dots(counter);
		printf("IntLit(%s)\n", factor->tokenOp);
		break;

	case RealLit:
		print_dots(counter);
		printf("RealLit(%s)\n", factor->tokenOp);
		break;

	case Id:
		if(factor->paramList != NULL){
			print_dots(counter);		
			printf("Call\n");
		}

		print_dots(counter);
		print_id(factor->tokenOp);
		
		while(factor->paramList != NULL){
			print_Expr(factor->paramList->expr, counter + 2);			
			factor->paramList = factor->paramList->next;
		}

		break;
	}
}

void print_WriteInPList(WriteInPList *writeInPList, int counter){
	while(writeInPList != NULL){
		if(writeInPList->optional->type == 1){
			print_Expr(writeInPList->optional->OptionalUnion.expr, counter);
		}

		else{			
			print_dots(counter);
			printf("String(%s)\n", writeInPList->optional->OptionalUnion.string);
		}

		writeInPList = writeInPList->next;
	}
}

void print_id(char *id){
	printf("Id(%s)\n", id);
}

void print_dots(int counter){
	int i;

	for(i = 0; i < counter; ++i){
		printf(".");
	}
}
