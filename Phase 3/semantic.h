#ifndef _SEMANTIC_
#define _SEMANTIC_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

typedef struct _SymbolTableLine SymbolTableLine;
typedef struct _SymbolTableHeader SymbolTableHeader;
struct _SymbolTableHeader{
	SymbolTableHeader *next;
	char *header_name;
	SymbolTableLine *symbolTableLine;
};

struct _SymbolTableLine{
	char *name;
	char *type;
	char *flag;
	char *value;
	SymbolTableLine *next;
};

enum{
	OuterSymbolTable = 0,
	FunctionSymbolTable = 1,
	ProgramSymbolTable = 2,

	boolean = 0,
	integer = 1,
	real = 2,
	False = 3,
	True = 4,
	Paramcount = 5,
	prog = 6,

	_type_ = 0,
	_boolean_ = 1,
	_function_ = 2,
	_program_ = 3,
	_integer_ = 4,
	_real_ = 5,

	Return = 0,
	Param = 1,
	VarParam = 2,
	Constant = 3,

	value_boolean = 0,
	value_integer = 1,
	value_real = 2,
	value_true = 3,
	value_false = 4
};

char *table_name[] = {"===== Outer Symbol Table =====", "===== Function Symbol Table =====", "===== Program Symbol Table ====="};
char *symbols[] = {"boolean", "integer", "real", "false", "true", "paramcount", "program"};
char *type[] = {"_type_", "_boolean_", "_function_", "_program_", "_integer_", "_real_"};
char *flag[] = {"return", "param", "varparam", "constant"};
char *value[] = {"_boolean_", "_integer_", "_real_", "_true_", "_false_"};


/* create symbol table */
SymbolTableHeader *create_table(Program *program);
SymbolTableLine *create_first_line(char *name, char *type, char *flag, char *value);
void insert_line_table(SymbolTableLine *temp, char *name, char *type, char *flag, char *value);
void create_default_function_symbol_table(SymbolTableHeader *temp);
void iterate_ast(Program *program, SymbolTableHeader *symbolTableHeader, SymbolTableHeader *last_pos);
SymbolTableHeader *declaration_table(SymbolTableHeader *temp, char *table);
int type_var(char *t);
char *to_lower_case(char *str);

/* print symbol table */
void print_semantic(SymbolTableHeader *symbolTableHeader);

/* error finding */
int verifyRepeatDeclaration(SymbolTableHeader *tab, char *var);


/* create symbol table */
SymbolTableHeader *create_table(Program *program){
	SymbolTableHeader *symbolTableHeader, *last_pos;

	symbolTableHeader = (SymbolTableHeader *)calloc(1, sizeof(SymbolTableHeader));
	symbolTableHeader->header_name = table_name[OuterSymbolTable];

	symbolTableHeader->symbolTableLine = create_first_line(symbols[boolean], type[_type_], flag[Constant], value[value_boolean]);
	insert_line_table(symbolTableHeader->symbolTableLine, symbols[integer], type[_type_], flag[Constant], value[value_integer]);
	insert_line_table(symbolTableHeader->symbolTableLine, symbols[real], type[_type_], flag[Constant], value[value_real]);
	insert_line_table(symbolTableHeader->symbolTableLine, symbols[False], type[_boolean_], flag[Constant], value[value_false]);
	insert_line_table(symbolTableHeader->symbolTableLine, symbols[True], type[_boolean_], flag[Constant], value[value_true]);
	insert_line_table(symbolTableHeader->symbolTableLine, symbols[Paramcount], type[_function_], NULL, NULL);
	insert_line_table(symbolTableHeader->symbolTableLine, symbols[prog], type[_program_], NULL, NULL);

	create_default_function_symbol_table(symbolTableHeader);

	last_pos = declaration_table(symbolTableHeader, table_name[ProgramSymbolTable]);
	iterate_ast(program, symbolTableHeader, last_pos);

	return symbolTableHeader;
}

SymbolTableLine *create_first_line(char *name, char *type, char *flag, char *value){
	SymbolTableLine *temp = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));

	temp->name = name;
	temp->type = type;
	temp->flag = flag;
	temp->value = value;

	return temp;
}

void insert_line_table(SymbolTableLine *temp, char *name, char *type, char *flag, char *value){
	SymbolTableLine *new, *aux = temp;

	new = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));

	while(aux->next != NULL){
		aux = aux->next;
	}

	new->name = name;
	new->type = type;
	new->flag = flag;
	new->value = value;
	aux->next = new;
}

void create_default_function_symbol_table(SymbolTableHeader *temp){
	SymbolTableHeader *new, *aux = temp;

	new = (SymbolTableHeader *)calloc(1, sizeof(SymbolTableHeader));

	while(aux->next != NULL){
		aux = aux->next;
	}

	new->header_name = table_name[FunctionSymbolTable];
	new->symbolTableLine = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));
	new->symbolTableLine->name = symbols[Paramcount];
	new->symbolTableLine->type = type[_integer_];
	new->symbolTableLine->flag = flag[Return];
	new->symbolTableLine->value = NULL;
	aux->next = new;
}

SymbolTableHeader *declaration_table(SymbolTableHeader *temp, char *table){
	SymbolTableHeader *new, *aux = temp;

	new = (SymbolTableHeader *)calloc(1, sizeof(SymbolTableHeader));

	while(aux->next != NULL){
		aux = aux->next;
	}

	new->header_name = table;
	aux->next = new;

	return aux->next;
}

void iterate_ast(Program *program, SymbolTableHeader *symbolTableHeader, SymbolTableHeader *last_pos){
	SymbolTableHeader *aux;
	SymbolTableLine *aux2;
	Program *temp, *save, *temp2;
	int t, f, check;
	char *normalValue;

	if(program != NULL){
		if(strcmp(program->type, "VarDecl") == 0){
			temp = program->son;

			while(temp->brother != NULL){
				temp = temp->brother;
			}

			normalValue = (char *)calloc(1, sizeof(char));
			strcpy(normalValue, temp->value);
			t = type_var(temp->value);

			if(t == -1){
				check = 0;
				aux2 = symbolTableHeader->symbolTableLine;

				while(aux2 != NULL){
					if(strcmp(temp->value, aux2->name) == 0){
						check = 1;
					}

					aux2 = aux2->next;
				}

				aux2 = symbolTableHeader->next->next->symbolTableLine;
				
				while(aux2 != NULL){
					if(strcmp(temp->value, aux2->name) == 0){
						check = 1;
					}

					aux2 = aux2->next;
				}

				strcpy(temp->value,normalValue);

				if(check == 0){
					symbolNotDefined_error(temp);
					return;
				}

				else{
					typeIdentifierExpected_error(temp);
					return;
				}
			}

			strcpy(temp->value,normalValue);

			while(program->son->brother != NULL){
				if(last_pos->symbolTableLine != NULL){
					normalValue = (char *)calloc(1, sizeof(char));
					strcpy(normalValue, program->son->value);
					check = verifyRepeatDeclaration(last_pos, to_lower_case(program->son->value));
					strcpy(program->son->value, normalValue);
					
					if(check == 1){
						symbolAlreadyDefined_error(program->son);
						return;
					}
				}

				if(last_pos->symbolTableLine == NULL){
					last_pos->symbolTableLine = create_first_line(to_lower_case(program->son->value), type[t], NULL, NULL);
				}

				else{
					insert_line_table(last_pos->symbolTableLine, to_lower_case(program->son->value), type[t], NULL, NULL);
				}

				program->son = program->son->brother;
			}
		}

		else if(strcmp(program->type, "FuncPart") == 0){
			temp = program;

			while(temp->son != NULL && (strcmp(temp->son->type, "FuncDecl") != 0 || strcmp(temp->son->type, "FuncDef") != 0) && (strcmp(temp->type, "FuncPart") == 0 || strcmp(temp->type, "NoPrint") == 0)){
				if(strcmp(temp->son->type, "FuncDef2") != 0){
					if(last_pos->symbolTableLine == NULL){
						last_pos->symbolTableLine = create_first_line(to_lower_case(temp->son->son->value), type[_function_], NULL, NULL);
					}

					else{
						insert_line_table(last_pos->symbolTableLine, to_lower_case(temp->son->son->value), type[_function_], NULL, NULL);
					}
				}

				temp = temp->brother;
			}

			iterate_ast(program->son, symbolTableHeader, last_pos);
		}

		else if(strcmp(program->type, "FuncDef") == 0){
			aux = declaration_table(symbolTableHeader, table_name[FunctionSymbolTable]);

			temp = program->son;

			while(strcmp(temp->brother->type, "VarPart") != 0){
				temp = temp->brother;				
			}

			save = temp->brother;
			t = type_var(temp->value);

			aux->symbolTableLine = create_first_line(to_lower_case(program->son->value), type[t], flag[Return], NULL);

			temp2 = program->son->brother;

			while(temp2->son != NULL && strcmp(temp2->son->type, "Id") != 0){
				temp = temp2->son->son;

				while(temp->brother != NULL){
					temp = temp->brother;
				}			

				t = type_var(temp->value);

				temp = temp2->son->son;

				if(strcmp(temp2->son->type, "VarParams") == 0){
					f = VarParam;
				}

				else{
					f = Param;
				}

				while(temp->brother != NULL){
					insert_line_table(aux->symbolTableLine, to_lower_case(temp->value), type[t], flag[f], NULL);
					temp = temp->brother;
				}

				temp2 = temp2->brother;
			}

			while(save->son != NULL && (strcmp(save->son->type, "NoPrint") == 0 || strcmp(save->son->type, "VarDecl") == 0)){
				temp = save->son->son;

				while(temp->brother != NULL){
					temp = temp->brother;
				}			

				t = type_var(temp->value);

				temp = save->son->son;

				while(temp->brother != NULL){
					insert_line_table(aux->symbolTableLine, to_lower_case(temp->value), type[t], NULL, NULL);			
					temp = temp->brother;
				}

				save = save->brother;
			}
		}

		else if(strcmp(program->type, "FuncDecl") == 0){
			aux = declaration_table(symbolTableHeader, table_name[FunctionSymbolTable]);

			temp = program->son;

			while(strcmp(temp->brother->type, "Id") != 0){
				temp = temp->brother;				
			}

			t = type_var(temp->brother->value);

			aux->symbolTableLine = create_first_line(to_lower_case(program->son->value), type[t], flag[Return], NULL);

			temp2 = program->son->brother;

			while(temp2->son != NULL && strcmp(temp2->son->type, "Id") != 0){
				temp = temp2->son->son;

				while(temp->brother != NULL){
					temp = temp->brother;
				}			

				t = type_var(temp->value);

				temp = temp2->son->son;

				if(strcmp(temp2->son->type, "VarParams") == 0){
					f = VarParam;
				}

				else{
					f = Param;
				}

				while(temp->brother != NULL){
					insert_line_table(aux->symbolTableLine, to_lower_case(temp->value), type[t], flag[f], NULL);
					temp = temp->brother;
				}

				temp2 = temp2->brother;
			}
		}

		else if(strcmp(program->type, "FuncDef2") == 0){
			temp2 = program->son->brother;

			aux = symbolTableHeader->next->next->next;

			while(aux != NULL && strcmp(to_lower_case(program->son->value), aux->symbolTableLine->name) != 0){
				aux = aux->next;
			}

			while(temp2->son != NULL && (strcmp(temp2->son->type, "NoPrint") == 0 || strcmp(temp2->son->type, "VarDecl") == 0)){
				temp = temp2->son->son;

				while(temp->brother != NULL){
					temp = temp->brother;
				}			

				t = type_var(temp->value);

				temp = temp2->son->son;

				while(temp->brother != NULL){
					insert_line_table(aux->symbolTableLine, to_lower_case(temp->value), type[t], NULL, NULL);			
					temp = temp->brother;
				}

				temp2 = temp2->brother;
			}
		}

		else{
			iterate_ast(program->son, symbolTableHeader, last_pos);
		}

		iterate_ast(program->brother, symbolTableHeader, last_pos);
	}
}

int type_var(char *t){
	if(strcmp(to_lower_case(t), "integer") == 0){
		return _integer_;
	}

	else if(strcmp(to_lower_case(t), "boolean") == 0){
		return _boolean_;
	}

	else if(strcmp(to_lower_case(t), "real") == 0){
		return _real_;
	}

	return -1;
}

char *to_lower_case(char *str){
	int i;

	for(i = 0; str[i]; ++i){
 		str[i] = tolower(str[i]);
	}

	return str;
}

/* print symbol table */
void print_semantic(SymbolTableHeader *symbolTableHeader){
	while(symbolTableHeader != NULL){
		printf("%s\n", symbolTableHeader->header_name);

		while(symbolTableHeader->symbolTableLine != NULL){
			printf("%s\t%s", symbolTableHeader->symbolTableLine->name, symbolTableHeader->symbolTableLine->type);

			if(symbolTableHeader->symbolTableLine->flag != NULL){
				printf("\t%s", symbolTableHeader->symbolTableLine->flag);

				if(symbolTableHeader->symbolTableLine->value != NULL){
					printf("\t%s", symbolTableHeader->symbolTableLine->value);
				}
			} 

			printf("\n");
			symbolTableHeader->symbolTableLine = symbolTableHeader->symbolTableLine->next;
		}
		
		symbolTableHeader = symbolTableHeader->next;

		if(symbolTableHeader != NULL){
			printf("\n");
		}
	}
}

/* error finding */
int verifyRepeatDeclaration(SymbolTableHeader *tab, char *var){
	SymbolTableLine *line = tab->symbolTableLine;

	while(line != NULL){
		if(strcmp(line->name, var) == 0){
			return 1;
		}

		line = line->next;
	}

	return 0;
}

#endif
