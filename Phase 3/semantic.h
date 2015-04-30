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

#endif
