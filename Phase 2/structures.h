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

typedef struct VarParams{
	char* first_id;
	char* last_id;
	IdStruct* id;
}VarParams;

typedef struct Params{
	char* first_id;
	char* last_id;
	IdStruct* id;
}Params;

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
struct FuncPart{
	FuncPart* next;

	/* everything is optional */
	union{
		FuncDecl* funcDecl;
		FuncDef* funcDef;
		FuncDef2* funcDef2;
	}funcPart;
};

struct ProgBlock{
	VarPart* varPart;
	FuncPart* funcPart;
	Statements stat;
};

#endif
