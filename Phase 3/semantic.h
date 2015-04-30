#ifndef _SEMANTIC_
#define _SEMANTIC_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
SymbolTableHeader *create_table();
SymbolTableHeader *create_outer_symbol_table();
SymbolTableHeader *create_function_symbol_table();

/* print symbol table */
void print_semantic(SymbolTableHeader *symbolTableHeader);
void print_outer_symbol_table(SymbolTableHeader *symbolTableHeader);
void print_function_symbol_table(char *header_name, SymbolTableLine *symbolTableLine);


/* create symbol table */
SymbolTableHeader *create_table(){
	SymbolTableHeader *symbolTableHeader;

	symbolTableHeader = create_outer_symbol_table();
	symbolTableHeader->next = create_function_symbol_table();

	return symbolTableHeader;
}

SymbolTableHeader *create_outer_symbol_table(){
	SymbolTableHeader *symbolTableHeader = (SymbolTableHeader *)calloc(1, sizeof(SymbolTableHeader));
	SymbolTableLine *temp;

	symbolTableHeader->header_name = table_name[OuterSymbolTable];
	symbolTableHeader->symbolTableLine = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));
	symbolTableHeader->symbolTableLine->name = symbols[boolean];
	symbolTableHeader->symbolTableLine->type = type[_type_];
	symbolTableHeader->symbolTableLine->flag = flag[Constant];
	symbolTableHeader->symbolTableLine->value = value[value_boolean];
	temp = symbolTableHeader->symbolTableLine;

	temp = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));
	temp->name = symbols[integer];
	temp->type = type[_type_];
	temp->flag = flag[Constant];
	temp->value = value[value_integer];
	temp = temp->next;

	temp = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));
	temp->name = symbols[real];
	temp->type = type[_type_];
	temp->flag = flag[Constant];
	temp->value = value[value_real];
	temp = temp->next;

	temp = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));
	temp->name = symbols[False];
	temp->type = type[_boolean_];
	temp->flag = flag[Constant];
	temp->value = value[value_false];
	temp = temp->next;

	temp = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));
	temp->name = symbols[True];
	temp->type = type[_boolean_];
	temp->flag = flag[Constant];
	temp->value = value[value_true];
	temp = temp->next;

	temp = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));
	temp->name = symbols[Paramcount];
	temp->type = type[_function_];
	temp->flag = NULL;
	temp->value = NULL;
	temp = temp->next;

	temp = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));
	temp->name = symbols[prog];
	temp->type = type[_program_];
	temp->flag = NULL;
	temp->value = NULL;
	temp->next = NULL;

	return symbolTableHeader;
}

SymbolTableHeader *create_function_symbol_table(){
	SymbolTableHeader *symbolTableHeader = (SymbolTableHeader *)calloc(1, sizeof(SymbolTableHeader));

	symbolTableHeader->header_name = table_name[FunctionSymbolTable];
	symbolTableHeader->symbolTableLine = (SymbolTableLine *)calloc(1, sizeof(SymbolTableLine));
	symbolTableHeader->symbolTableLine->name = symbols[Paramcount];
	symbolTableHeader->symbolTableLine->type = type[_integer_];
	symbolTableHeader->symbolTableLine->flag = flag[Return];
	symbolTableHeader->symbolTableLine->value = NULL;

	return symbolTableHeader;
}


/* print symbol table */
void print_semantic(SymbolTableHeader *symbolTableHeader){
	print_outer_symbol_table(symbolTableHeader);
	print_function_symbol_table(symbolTableHeader->header_name, symbolTableHeader->symbolTableLine);
}

void print_outer_symbol_table(SymbolTableHeader *symbolTableHeader){
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

	printf("\n");
}

void print_function_symbol_table(char *header_name, SymbolTableLine *symbolTableLine){
	printf("%s\n", header_name);
	printf("%s\t%s\t%s\n\n", symbolTableLine->name, symbolTableLine->type, symbolTableLine->flag);
}

#endif
