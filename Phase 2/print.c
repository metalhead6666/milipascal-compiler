#include "print.h"

void print_tree(Program* program){
	int counter = 0;
	printf("Program\n");

	print_dots(counter);
	print_id(program->id);

	print_varPart(program->progBlock->varPart, counter + 2);
	print_funcPart(program->progBlock->funcPart, counter + 2);
	print_statList(program->progBlock->stat, 1, counter + 2);
}

void print_varPart(VarPart* varPart, int counter){
	print_dots(counter);
	printf("VarPart\n");

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

	print_dots(counter);
	printf("FuncPart\n");

	counter += 2;

	while(funcPart != NULL){
		print_dots(counter);
		printf("FuncDecl\n");		
		
		counter += 2;
		print_dots(counter);
		
		if(funcPart->funcDeclaration->type == 1){
			funcHeading = funcPart->funcDeclaration->funcDeclarationUnion.funcHeading;
			
			print_id(funcHeading->first_id);
			counter += 2;

			while(funcHeading->next != NULL && funcHeading->next->formalParams != NULL){
				print_dots(counter);
				print_id(funcHeading->next->formalParams->first_id);

				print_IdStruct(funcHeading->next->formalParams->idStruct, counter);
				
				print_dots(counter);			
				print_id(funcHeading->next->formalParams->last_id);
				
				funcHeading->next = funcHeading->next->next;
			}

			counter -= 2;
			
			print_dots(counter);
			print_id(funcHeading->last_id);
		}

		else{
			print_id(funcPart->funcDeclaration->funcDeclarationUnion.id);
		}
		
		print_varPart(funcPart->funcDeclaration->varPart, counter + 2);
		print_statList(funcPart->funcDeclaration->stat, 1, counter + 2);
		funcPart = funcPart->next;

		counter -= 2;		
	}
}

void print_statList(StatList *statList, int verbose, int counter){
	if(verbose == 1){
		print_dots(counter);
		printf("StatList\n");
	}

	while(statList != NULL){
		while(statList->stat != NULL){			
			printStatements(statList->stat->statement, counter + 2);
			
			print_Expr(statList->stat->expr, counter + 4);
			print_WriteInPList(statList->stat->writeInPList, counter + 4);

			if(statList->stat->type == 1){
				print_dots(counter + 4);
				print_id(statList->stat->StatUnion.id);
			}

			else if(statList->stat->type == 2){				
				print_statList(statList->stat->StatUnion.statList, 0, counter);				
			}

			statList->stat = statList->stat->next;
		}		

		statList = statList->next;
	}
}

void printStatements(Statements statement, int counter){
	print_dots(counter);

	switch(statement){
	case Assign:				
		printf("Assign\n");
		break;

	case IfElse:
		printf("IfElse\n");		
		break;

	case Repeat:
		printf("Repeat\n");
		break;

	case StatList1:
		printf("StatList\n");
		break;

	case ValParam:
		printf("ValParam\n");
		break;

	case While:
		printf("While\n");
		break;

	case WriteLn:
		printf("WriteLn\n");
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
		print_term(simpleExpr->term, counter);
		
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
		print_dots(counter);
		print_id(factor->tokenOp);	
		
		while(factor->paramList != NULL){
			print_dots(counter + 2);
			printf("Call\n");			
			print_Expr(factor->paramList->expr, counter + 2);			
			factor->paramList = factor->paramList->next;
		}

		break;
	}
}

void print_WriteInPList(WriteInPList *writeInPList, int counter){
	while(writeInPList != NULL){
		if(writeInPList->optional->type == 1){
			print_Expr(writeInPList->optional->OptionalUnion.expr, counter + 2);
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
