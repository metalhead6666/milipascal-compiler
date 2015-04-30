#ifndef _SEMANTIC_
#define _SEMANTIC

typedef enum _ErrorType{
	CannotWriteValues,
	FunctionIdentifierExpected,
	IncompatibleTypeArgument,
	IncompatibleTypeAssignment,
	IncompatibleTypeStatement,
	CannotAppliedType,
	CannotAppliedType2,
	SymbolAlreadyDefined,
	SymbolNotDefined,
	TypeIdentifierExpected,
	VariableIdentifierExpected,
	WrongNumberArguments
}ErrorType;

typedef struct _ErrorStruct{
	int number;
	char *tok_stat;
	char *type1;
	char *type2;
	ErrorType errorType;
}ErrorStruct;


void create_table();
void print_semantic();


void create_table(){

}

void print_semantic(){

}

#endif
