#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef enum Terminals{
	Id,
	IntLit, 
	RealLit, 
	String
}Terminals;

typedef enum Operators{
	Add,
	And,
	Call,
	Div,
	Eq,
	Geq,
	Gt,
	Leq,
	Lt,
	Minus,
	Mod,
	Mul,
	Neq,
	Not,
	Or,
	Plus,
	RealDiv,
	Sub
}Operators;

typedef enum Statements{
	Assign,
	IfElse,
	Repeat,
	StatList,
	ValParam,
	While,
	WriteLn
}Statements;

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
	Statements stat;
	VarPart* varPart;
	union{
		char *id;
		FuncHeading* funcHeading;
	}funcDeclarationUnion;
}FuncDeclaration;

struct FuncPart{
	FuncPart* next;
	FuncDeclaration *funcDeclaration;
};

struct ProgBlock{
	VarPart* varPart;
	FuncPart* funcPart;
	Statements stat;
};





#endif
