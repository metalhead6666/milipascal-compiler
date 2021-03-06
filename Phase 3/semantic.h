#ifndef _SEMANTIC_
#define _SEMANTIC_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

extern int hasErrorsSemantic;

/* function declaration */
extern void cannotWriteValues_error(char* type);
extern void functionIdentifierExpected_error(Program *p);
extern void incompatibleTypeArgument_error(Program *p, int num, char *token, char *type1, char *type2);
extern void incompatibleTypeAssigment_error(Program *p, char *token, char *type1, char *type2);
extern void incompatibleTypeStatement_error(char *statement, char *type1, char *type2);
extern void cannotAppliedType_error(char *token, char *type);
extern void cannotAppliedType2_error(char *token, char *type1, char *type2);
extern void symbolAlreadyDefined_error(Program *p);
extern void symbolNotDefined_error(Program *p);
extern void typeIdentifierExpected_error(Program *p);
extern void variableIdentifierExpected_error();
extern void wrongNumberArguments_error(Program *p, char *token, int type1, int type2);

typedef struct _SymbolTableLine SymbolTableLine;
typedef struct _SymbolTableHeader SymbolTableHeader;
struct _SymbolTableHeader{
	SymbolTableHeader *next;
	int defined;
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
SymbolTableHeader *declaration_table(SymbolTableHeader *temp, char *table, int num);
SymbolTableHeader *last_pos_symbol(char *value, int t, SymbolTableHeader *last_pos);
void insert_line_func(Program *program, SymbolTableHeader *aux);
void insert_line_var_decl(Program *program, SymbolTableHeader *aux);
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

	last_pos = declaration_table(symbolTableHeader, table_name[ProgramSymbolTable], 42);
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

SymbolTableHeader *declaration_table(SymbolTableHeader *temp, char *table, int num){
	SymbolTableHeader *new, *aux = temp;

	new = (SymbolTableHeader *)calloc(1, sizeof(SymbolTableHeader));

	while(aux->next != NULL){
		aux = aux->next;
	}

	new->header_name = table;
	new->defined = num;
	aux->next = new;

	return aux->next;
}


void iterate_ast(Program *program, SymbolTableHeader *symbolTableHeader, SymbolTableHeader *last_pos){
	SymbolTableHeader *aux, *aux4;
	SymbolTableLine *aux2, *aux3;
	Program *temp, *save;
	int t, check, counter, counter2;
	char *normalValue;

	if(program != NULL && !hasErrorsSemantic){
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

				strcpy(temp->value, normalValue);

				if(check == 0){
					symbolNotDefined_error(temp);
					return;
				}

				else{
					typeIdentifierExpected_error(temp);
					return;
				}
			}

			strcpy(temp->value, normalValue);

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

				last_pos = last_pos_symbol(program->son->value, t, last_pos);

				program->son = program->son->brother;
			}
		}

		else if(strcmp(program->type, "FuncPart") == 0){
			temp = program;

			while(temp->son != NULL && (strcmp(temp->son->type, "FuncDecl") != 0 || strcmp(temp->son->type, "FuncDef") != 0) && (strcmp(temp->type, "FuncPart") == 0 || strcmp(temp->type, "NoPrint") == 0)){
				if(strcmp(temp->son->type, "FuncDef2") != 0){
					aux2 = last_pos->symbolTableLine;
					normalValue = (char *)calloc(1, sizeof(char));

					while(aux2 != NULL){						
						strcpy(normalValue, temp->son->son->value);

						if(strcmp(to_lower_case(normalValue), aux2->name) == 0){
							symbolAlreadyDefined_error(temp->son->son);
							return;
						}

						aux2 = aux2->next;
					}

					last_pos = last_pos_symbol(temp->son->son->value, _function_, last_pos);
				}

				temp = temp->brother;
			}

			iterate_ast(program->son, symbolTableHeader, last_pos);
		}

		else if(strcmp(program->type, "FuncDef") == 0){
			aux = declaration_table(symbolTableHeader, table_name[FunctionSymbolTable], 2);

			temp = program->son;

			while(strcmp(temp->brother->type, "VarPart") != 0){
				temp = temp->brother;				
			}

			save = temp->brother;

			normalValue = (char *)calloc(1, sizeof(char));
			strcpy(normalValue, temp->value);
			t = type_var(normalValue);

			if(t == -1){
				aux2 = last_pos->symbolTableLine;

				while(aux2 != NULL){
					if(strcmp(aux2->name, normalValue) == 0){
						typeIdentifierExpected_error(temp);
						return;
					}

					aux2 = aux2->next;
				}

				symbolNotDefined_error(temp);
				return;
			}

			aux->symbolTableLine = create_first_line(to_lower_case(program->son->value), type[t], flag[Return], NULL);

			insert_line_func(program->son->brother, aux);
			insert_line_var_decl(save, aux);

			temp = program->son->brother;
			aux4 = aux;

			while(temp != NULL){				
				while(temp->son != NULL){
					if(strcmp(temp->son->type, "Call") == 0){
						counter2 = 1;
						counter = 0;
						check = 0;
						normalValue = (char *)calloc(1, sizeof(char));
						strcpy(normalValue, temp->son->son->value);

						aux2 = last_pos->symbolTableLine;

						while(aux2 != NULL){
							if(strcmp(aux2->name, to_lower_case(normalValue)) == 0){
								if(strcmp(aux2->type, type[_function_]) == 0){
									check = 1;
									break;
								}

								break;
							}

							aux2 = aux2->next;							
						}

						if(!check){
							functionIdentifierExpected_error(temp->son->son);
							return;
						}

						aux = symbolTableHeader->next->next->next;

						while(aux != NULL && strcmp(to_lower_case(normalValue), aux->symbolTableLine->name) != 0){
							aux = aux->next;
						}

						aux2 = aux->symbolTableLine->next;

						while(aux2 != NULL){
							if(aux2->flag != NULL){
								++counter;
							}

							aux2 = aux2->next;
						}

						save = temp->son->son->brother;

						while(save->brother != NULL){
							++counter2;
							save = save->brother;
						}

						if(counter != counter2){
							wrongNumberArguments_error(temp->son->son, temp->son->son->value, counter2, counter);
							return;
						}

						aux2 = aux->symbolTableLine->next;
						aux = symbolTableHeader->next->next->next;

						while(aux != NULL && strcmp(to_lower_case(program->son->value), aux->symbolTableLine->name) != 0){
							aux = aux->next;
						}

						save = temp->son->son->brother;
						counter = 1;						

						while(save != NULL && aux2->flag != NULL){
							if(strcmp(save->type, "IntLit") == 0){
								if(strcmp(aux2->flag, flag[Param]) == 0){
									if(strcmp(aux2->type, type[_integer_]) != 0 && strcmp(aux2->type, type[_real_]) != 0){
										incompatibleTypeArgument_error(save, counter, program->son->value, type[_integer_], aux2->type);
										return;
									}
								}

								else{
									if(strcmp(aux2->type, type[_integer_]) != 0){
										incompatibleTypeArgument_error(save, counter, program->son->value, type[_integer_], aux2->type);
										return;
									}
								}					
							}

							if(strcmp(save->type, "RealLit") == 0 && strcmp(aux2->type, type[_real_]) != 0){
								incompatibleTypeArgument_error(save, counter, program->son->value, type[_real_], aux2->type);
								return;
							}

							if(strcmp(save->type, "Id") == 0){
								if((strcmp(to_lower_case(save->value), "true") == 0 || strcmp(to_lower_case(save->value), "false") == 0) && strcmp(aux2->type, type[_boolean_]) != 0){
									incompatibleTypeArgument_error(save, counter, program->son->value, type[_boolean_], aux2->type);
									return;
								}

								aux3 = last_pos->symbolTableLine;
								strcpy(normalValue, save->value);

								while(aux3 != NULL){
									if(strcmp(to_lower_case(normalValue), aux3->name) == 0){										
										incompatibleTypeArgument_error(save, counter, program->son->value, aux3->type, aux2->type);
										return;
									}

									aux3 = aux3->next;
								}

								aux3 = aux->symbolTableLine->next;

								while(aux3 != NULL){
									if(strcmp(to_lower_case(normalValue), aux3->name) == 0){										
										incompatibleTypeArgument_error(save, counter, program->son->value, aux3->type, aux2->type);
										return;
									}

									aux3 = aux3->next;
								}
							}

							++counter;
							save = save->brother;
							aux2 = aux2->next;
						}

						break;
					}

					else if(strcmp(temp->son->type, "Assign") == 0){
						char *s = (char *)calloc(1, sizeof(char));
						strcpy(s, program->son->value);
						normalValue = (char *)calloc(1, sizeof(char));
						strcpy(normalValue, temp->son->son->brother->value);						
						counter = 0;

						if(strcmp(to_lower_case(normalValue), to_lower_case(s)) == 0){
							aux2 = aux4->symbolTableLine->next;

							while(aux2 != NULL){
								if(aux2->flag != NULL){
									++counter;
								}

								aux2 = aux2->next;
							}

							if(counter > 0){
								wrongNumberArguments_error(temp->son->son->brother, temp->son->son->brother->value, 0, counter);
								return;
							}	
						}

						normalValue = (char *)calloc(1, sizeof(char));
						strcpy(normalValue, program->son->value);
						
						if(strcmp(to_lower_case(normalValue), temp->son->son->value) == 0){
							aux2 = aux4->symbolTableLine;
							save = temp->son->son->brother;
							normalValue = (char *)calloc(1, sizeof(char));
							strcpy(normalValue, save->value);

							while(save != NULL){
								while(aux2 != NULL){
									if(strcmp(normalValue, aux2->name) == 0){
										if(strcmp(aux2->type, aux4->symbolTableLine->type) != 0){
											incompatibleTypeAssigment_error(temp->son->son, program->son->value, aux2->type, aux4->symbolTableLine->type);
											return;
										}
									}

									aux2 = aux2->next;
								}

								save = save->brother;
							}
						}						
					}

					temp->son = temp->son->brother;
				}

				/*if(strcmp(temp->type, "Assign") == 0){
					normalValue = (char *)calloc(1, sizeof(char));
					strcpy(normalValue, program->son->value);
					
					if(strcmp(to_lower_case(normalValue), temp->son->value) == 0){
						aux2 = aux4->symbolTableLine;
						save = temp->son->brother;
						normalValue = (char *)calloc(1, sizeof(char));
						strcpy(normalValue, save->value);

						while(save != NULL){
							while(aux2 != NULL){
								if(strcmp(normalValue, aux2->name) == 0){
									if(strcmp(aux2->type, aux4->symbolTableLine->type) != 0){
										incompatibleTypeAssigment_error(temp->son, program->son->value, aux2->type, aux4->symbolTableLine->type);
										return;
									}
								}

								aux2 = aux2->next;
							}

							save = save->brother;
						}
					}

					char *s = (char *)calloc(1, sizeof(char));
					strcpy(s, program->son->value);
					normalValue = (char *)calloc(1, sizeof(char));
					strcpy(normalValue, temp->son->brother->value);			
					counter = 0;

					if(strcmp(to_lower_case(normalValue), to_lower_case(s)) == 0){
						aux2 = aux4->symbolTableLine->next;

						while(aux2 != NULL){
							if(aux2->flag != NULL){
								++counter;
							}

							aux2 = aux2->next;
						}

						if(counter > 0){
							wrongNumberArguments_error(temp->son->brother, temp->son->brother->value, 0, counter);
							return;
						}
					}
				}*/

				temp = temp->brother;
			}
		}

		else if(strcmp(program->type, "FuncDecl") == 0){
			aux = declaration_table(symbolTableHeader, table_name[FunctionSymbolTable], 1);

			temp = program->son;

			while(strcmp(temp->brother->type, "Id") != 0){
				temp = temp->brother;				
			}

			normalValue = (char *)calloc(1, sizeof(char));
			strcpy(normalValue, temp->brother->value);

			t = type_var(normalValue);

			if(t == -1){
				aux2 = last_pos->symbolTableLine;

				while(aux2 != NULL){
					if(strcmp(aux2->name, normalValue) == 0){
						typeIdentifierExpected_error(temp->brother);
						return;
					}

					aux2 = aux2->next;
				}

				symbolNotDefined_error(temp->brother);
				return;
			}

			aux->symbolTableLine = create_first_line(to_lower_case(program->son->value), type[t], flag[Return], NULL);
			insert_line_func(program->son->brother, aux);
		}

		else if(strcmp(program->type, "FuncDef2") == 0){
			aux = symbolTableHeader->next->next->next;
			normalValue = (char *)calloc(1, sizeof(char));
			strcpy(normalValue, program->son->value);

			while(aux != NULL && strcmp(to_lower_case(normalValue), aux->symbolTableLine->name) != 0){
				aux = aux->next;
			}

			if(aux == NULL){
				symbolNotDefined_error(program->son);
				return;
			}

			if(aux->defined == 2){
				symbolAlreadyDefined_error(program->son);
				return;
			}

			aux->defined = 2;

			insert_line_var_decl(program->son->brother, aux);
			aux4 = aux;

			temp = program->son->brother;

			while(temp != NULL){
				while(temp->son != NULL){
					if(strcmp(temp->son->type, "Call") == 0){
						counter2 = 1;
						counter = 0;
						check = 0;
						normalValue = (char *)calloc(1, sizeof(char));
						strcpy(normalValue, temp->son->son->value);

						aux2 = last_pos->symbolTableLine;

						while(aux2 != NULL){
							if(strcmp(aux2->name, to_lower_case(normalValue)) == 0){
								if(strcmp(aux2->type, type[_function_]) == 0){
									check = 1;
									break;
								}

								break;
							}

							aux2 = aux2->next;
							
						}

						if(!check){
							functionIdentifierExpected_error(temp->son->son);
							return;
						}

						aux = symbolTableHeader->next->next->next;

						while(aux != NULL && strcmp(to_lower_case(normalValue), aux->symbolTableLine->name) != 0){
							aux = aux->next;
						}

						aux2 = aux->symbolTableLine->next;

						while(aux2 != NULL){
							if(aux2->flag != NULL){
								++counter;
							}

							aux2 = aux2->next;
						}

						save = temp->son->son->brother;

						while(save->brother != NULL){
							++counter2;
							save = save->brother;
						}

						if(counter != counter2){
							wrongNumberArguments_error(temp->son->son, temp->son->son->value, counter2, counter);
							return;
						}

						aux2 = aux->symbolTableLine->next;
						aux = symbolTableHeader->next->next->next;

						while(aux != NULL && strcmp(to_lower_case(program->son->value), aux->symbolTableLine->name) != 0){
							aux = aux->next;
						}

						save = temp->son->son->brother;
						counter = 1;						

						while(save != NULL && aux2->flag != NULL){
							if(strcmp(save->type, "IntLit") == 0){
								if(strcmp(aux2->flag, flag[Param]) == 0){
									if(strcmp(aux2->type, type[_integer_]) != 0 && strcmp(aux2->type, type[_real_]) != 0){
										incompatibleTypeArgument_error(save, counter, program->son->value, type[_integer_], aux2->type);
										return;
									}
								}

								else{
									if(strcmp(aux2->type, type[_integer_]) != 0){
										incompatibleTypeArgument_error(save, counter, program->son->value, type[_integer_], aux2->type);
										return;
									}
								}					
							}

							if(strcmp(save->type, "RealLit") == 0 && strcmp(aux2->type, type[_real_]) != 0){
								incompatibleTypeArgument_error(save, counter, program->son->value, type[_real_], aux2->type);
								return;
							}							

							if(strcmp(save->type, "Id") == 0){
								if((strcmp(to_lower_case(save->value), "true") == 0 || strcmp(to_lower_case(save->value), "false") == 0) && strcmp(aux2->type, type[_boolean_]) != 0){
									incompatibleTypeArgument_error(save, counter, program->son->value, type[_boolean_], aux2->type);
									return;
								}

								aux3 = last_pos->symbolTableLine;
								strcpy(normalValue, save->value);

								while(aux3 != NULL){
									if(strcmp(to_lower_case(normalValue), aux3->name) == 0){										
										incompatibleTypeArgument_error(save, counter, program->son->value, aux3->type, aux2->type);
										return;
									}

									aux3 = aux3->next;
								}

								aux3 = aux->symbolTableLine->next;

								while(aux3 != NULL){
									if(strcmp(to_lower_case(normalValue), aux3->name) == 0){										
										incompatibleTypeArgument_error(save, counter, program->son->value, aux3->type, aux2->type);
										return;
									}

									aux3 = aux3->next;
								}
							}

							++counter;
							save = save->brother;
							aux2 = aux2->next;
						}

						break;
					}

					else if(strcmp(temp->son->type, "Assign") == 0){
						char *s = (char *)calloc(1, sizeof(char));
						strcpy(s, program->son->value);
						normalValue = (char *)calloc(1, sizeof(char));
						strcpy(normalValue, temp->son->son->brother->value);						
						counter = 0;

						if(strcmp(to_lower_case(normalValue), to_lower_case(s)) == 0){
							aux2 = aux4->symbolTableLine->next;

							while(aux2 != NULL){
								if(aux2->flag != NULL){
									++counter;
								}

								aux2 = aux2->next;
							}

							if(counter > 0){
								wrongNumberArguments_error(temp->son->son->brother, temp->son->son->brother->value, 0, counter);
								return;
							}
						}

						normalValue = (char *)calloc(1, sizeof(char));
						strcpy(normalValue, program->son->value);
						
						if(strcmp(to_lower_case(normalValue), temp->son->son->value) == 0){
							aux2 = aux4->symbolTableLine;
							save = temp->son->son->brother;
							normalValue = (char *)calloc(1, sizeof(char));
							strcpy(normalValue, save->value);

							while(save != NULL){
								while(aux2 != NULL){
									if(strcmp(normalValue, aux2->name) == 0){
										if(strcmp(aux2->type, aux4->symbolTableLine->type) != 0){
											incompatibleTypeAssigment_error(temp->son->son, program->son->value, aux2->type, aux4->symbolTableLine->type);
											return;
										}
									}

									aux2 = aux2->next;
								}

								save = save->brother;
							}
						}
					}

					temp->son = temp->son->brother;
				}

				/*if(strcmp(temp->type, "Assign") == 0){
					normalValue = (char *)calloc(1, sizeof(char));
					strcpy(normalValue, program->son->value);
					
					if(strcmp(to_lower_case(normalValue), temp->son->value) == 0){
						aux2 = aux4->symbolTableLine;
						save = temp->son->brother;
						normalValue = (char *)calloc(1, sizeof(char));
						strcpy(normalValue, save->value);

						while(save != NULL){
							while(aux2 != NULL){
								if(strcmp(normalValue, aux2->name) == 0){
									if(strcmp(aux2->type, aux4->symbolTableLine->type) != 0){
										incompatibleTypeAssigment_error(temp->son, program->son->value, aux2->type, aux4->symbolTableLine->type);
										return;
									}
								}

								aux2 = aux2->next;
							}

							save = save->brother;
						}
					}

					char *s = (char *)calloc(1, sizeof(char));
					strcpy(s, program->son->value);
					normalValue = (char *)calloc(1, sizeof(char));
					strcpy(normalValue, temp->son->brother->value);						
					counter = 0;

					if(strcmp(to_lower_case(normalValue), to_lower_case(s)) == 0){
						aux2 = aux4->symbolTableLine->next;

						while(aux2 != NULL){
							if(aux2->flag != NULL){
								++counter;
							}

							aux2 = aux2->next;
						}

						if(counter > 0){
							wrongNumberArguments_error(temp->son->brother, temp->son->brother->value, 0, counter);
							return;
						}
					}
				}*/

				temp = temp->brother;
			}
		}

		else if(strcmp(program->type, "Call") == 0){
			counter2 = 1;
			counter = 0;
			check = 0;

			aux2 = last_pos->symbolTableLine;
			normalValue = (char *)calloc(1, sizeof(char));
			strcpy(normalValue, program->son->value);

			while(aux2 != NULL){
				if(strcmp(aux2->name, to_lower_case(normalValue)) == 0){
					if(strcmp(aux2->type, type[_function_]) == 0){
						check = 1;
						break;
					}

					break;
				}

				aux2 = aux2->next;
			}

			if(!check){
				functionIdentifierExpected_error(program->son);
				return;
			}

			aux = symbolTableHeader->next->next->next;

			while(aux != NULL && strcmp(to_lower_case(normalValue), aux->symbolTableLine->name) != 0){
				aux = aux->next;
			}

			aux2 = aux->symbolTableLine->next;

			while(aux2 != NULL){
				if(aux2->flag != NULL){
					++counter;
				}

				aux2 = aux2->next;
			}

			temp = program->son->brother;

			while(temp->brother != NULL){
				++counter2;
				temp = temp->brother;
			}

			if(counter != counter2){
				wrongNumberArguments_error(program->son, program->son->value, counter2, counter);
				return;
			}

			temp = program->son->brother;
			aux2 = aux->symbolTableLine->next;
			counter = 1;

			while(temp != NULL && aux2->flag != NULL){
				if(strcmp(temp->type, "IntLit") == 0){
					if(strcmp(aux2->flag, flag[Param]) == 0){
						if(strcmp(aux2->type, type[_integer_]) != 0 && strcmp(aux2->type, type[_real_]) != 0){
							incompatibleTypeArgument_error(temp, counter, program->son->value, type[_integer_], aux2->type);
							return;
						}
					}

					else{
						if(strcmp(aux2->type, type[_integer_]) != 0){
							incompatibleTypeArgument_error(temp, counter, program->son->value, type[_integer_], aux2->type);
							return;
						}
					}					
				}

				if(strcmp(temp->type, "RealLit") == 0 && strcmp(aux2->type, type[_real_]) != 0){
					incompatibleTypeArgument_error(temp, counter, program->son->value, type[_real_], aux2->type);
					return;
				}

				if(strcmp(temp->type, "Id") == 0){
					if((strcmp(to_lower_case(temp->value), "true") == 0 || strcmp(to_lower_case(temp->value), "false") == 0) && strcmp(aux2->type, type[_boolean_]) != 0){
						incompatibleTypeArgument_error(temp, counter, program->son->value, type[_boolean_], aux2->type);
						return;
					}

					aux3 = last_pos->symbolTableLine;
					strcpy(normalValue, temp->value);

					while(aux3 != NULL){
						if(strcmp(to_lower_case(normalValue), aux3->name) == 0){
							incompatibleTypeArgument_error(temp, counter, program->son->value, aux3->type, aux2->type);
							return;
						}

						aux3 = aux3->next;
					}
				}

				++counter;
				temp = temp->brother;
				aux2 = aux2->next;
			}
		}

		else{
			iterate_ast(program->son, symbolTableHeader, last_pos);
		}

		iterate_ast(program->brother, symbolTableHeader, last_pos);
	}
}

SymbolTableHeader *last_pos_symbol(char *value, int t, SymbolTableHeader *last_pos){
	if(last_pos->symbolTableLine == NULL){
		last_pos->symbolTableLine = create_first_line(to_lower_case(value), type[t], NULL, NULL);
	}

	else{
		insert_line_table(last_pos->symbolTableLine, to_lower_case(value), type[t], NULL, NULL);
	}

	return last_pos;
}

void insert_line_func(Program *program, SymbolTableHeader *aux){
	SymbolTableLine *aux2;
	Program *temp, *temp2 = program;
	int t, f;
	char *normalValue;

	while(temp2->son != NULL && strcmp(temp2->son->type, "Id") != 0){
		temp = temp2->son->son;

		while(temp->brother != NULL){
			temp = temp->brother;
		}			

		normalValue = (char *)calloc(1, sizeof(char));
		strcpy(normalValue, temp->value);
		t = type_var(normalValue);

		temp = temp2->son->son;

		if(strcmp(temp2->son->type, "VarParams") == 0){
			f = VarParam;
		}

		else{
			f = Param;
		}

		while(temp->brother != NULL){
			aux2 = aux->symbolTableLine;
			normalValue = (char *)calloc(1, sizeof(char));
			strcpy(normalValue, temp->value);

			while(aux2 != NULL){
				if(strcmp(to_lower_case(normalValue), aux2->name) == 0){
					symbolAlreadyDefined_error(temp);
					return;
				}

				aux2 = aux2->next;
			}
			
			insert_line_table(aux->symbolTableLine, to_lower_case(temp->value), type[t], flag[f], NULL);

			temp = temp->brother;
		}

		temp2 = temp2->brother;
	}
}

void insert_line_var_decl(Program *program, SymbolTableHeader *aux){
	SymbolTableLine *aux2;
	Program *temp, *temp2 = program;
	char *normalValue;
	int t;

	while(temp2->son != NULL && (strcmp(temp2->son->type, "NoPrint") == 0 || strcmp(temp2->son->type, "VarDecl") == 0)){
		temp = temp2->son->son;

		while(temp->brother != NULL){
			temp = temp->brother;
		}			

		normalValue = (char *)calloc(1, sizeof(char));
		strcpy(normalValue, temp->value);
		t = type_var(normalValue);

		temp = temp2->son->son;

		while(temp->brother != NULL){
			aux2 = aux->symbolTableLine;			
			normalValue = (char *)calloc(1, sizeof(char));
			strcpy(normalValue, temp->value);

			while(aux2 != NULL){
				if(strcmp(to_lower_case(normalValue), aux2->name) == 0){
					symbolAlreadyDefined_error(temp);
					return;
				}

				aux2 = aux2->next;
			}

			insert_line_table(aux->symbolTableLine, to_lower_case(temp->value), type[t], NULL, NULL);

			temp = temp->brother;
		}

		temp2 = temp2->brother;
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
