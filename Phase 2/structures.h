#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef struct Stat Stat;
typedef struct Expr Expr;
typedef struct IdStruct IdStruct;
struct IdStruct{
	IdStruct* next;
	char* id;
};

typedef struct VarDecl{
	char* first_id;
	char* last_id;
	IdStruct* id;
}VarDecl;

typedef struct VarPart VarPart;
struct VarPart{
	VarPart* next;
	VarDecl* varDecl;
};

typedef struct ProgBlock ProgBlock;
/* Program */
typedef struct Program{
	char* id;
	ProgBlock* progBlock;
}Program;

typedef struct FuncPart FuncPart;
typedef struct FormalParams{
	char* first_id;
	IdStruct* idStruct;
	char* last_id;
}FormalParams;

typedef struct FormalParamList FormalParamList;
struct FormalParamList{
	FormalParams* formalParams;
	FormalParamList* next;
};

typedef struct FuncHeading{
	char* first_id;
	FormalParamList* next;
	char* last_id;
}FuncHeading;

typedef struct FuncDeclaration{
	Stat* stat;
	VarPart* varPart;
	
	union{
		char *id;
		FuncHeading* funcHeading;
	}funcDeclarationUnion;

	int type;
}FuncDeclaration;

struct FuncPart{
	FuncPart* next;
	FuncDeclaration *funcDeclaration;
};

struct ProgBlock{
	VarPart* varPart;
	FuncPart* funcPart;
	Stat* stat;
};

typedef struct StatList StatList;
struct StatList{
	Stat *stat;
	StatList *next;
};

typedef struct ParamList ParamList;
struct ParamList{
	Expr *expr;
	ParamList *next;
};	

typedef struct Factor Factor;
struct Factor{
	Expr *expr;
	char *tokenOp;
	ParamList *paramList;
	Factor *next;
};

typedef struct Term Term;
struct Term{
	Factor *factor;
	Term *next;
	char *multOp;
};

typedef struct SimpleExpr SimpleExpr;
struct SimpleExpr{
	Term *term;
	char* addOp;
	SimpleExpr *next;
};

struct Expr{
	SimpleExpr *first_simpleExpr;
	SimpleExpr *last_simpleExpr;
	char *relationalOp;
};

typedef struct Optional{
	union{
		Expr *expr;
		char *string;
	}OptionalUnion;

	int type;
}Optional;

typedef struct WriteInPList WriteInPList;
struct WriteInPList{
	Optional *optional;
	WriteInPList *next;
};

struct Stat{
	Expr *expr;
	Stat *next;
	WriteInPList * writeInPList;
	union{
		char *id;
		StatList *statList;
	}StatUnion;
	
	int type;
};

#endif
