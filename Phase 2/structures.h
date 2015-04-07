#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef enum{
	Id,
	IntLit, 
	RealLit, 
	String
}Terminals;

typedef enum{
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

typedef enum{
	Assign,
	IfElse,
	Repeat,
	StatList,
	ValParam,
	While,
	WriteLn
}Statements;

typedef struct _Program Program;
typedef struct _VarPart VarPart;
typedef struct _VarDecl VarDecl;
typedef struct _IdStruct IdStruct;
typedef struct _FuncPart FuncPart;
typedef struct _FuncDecl FuncDecl;
typedef struct _FuncDef FuncDef;
typedef struct _FuncDef2 FuncDef2;
typedef struct _FuncParams FuncParams;
typedef struct _Params Params;
typedef struct _VarParams VarParams;

//Program
struct _Program{
	char* id;
	VarPart* varPart;
	FuncPart* funcPart;
	Statements stat;
};

struct _VarPart{
	VarPart* next;
	VarDecl* varDecl;
};

struct _VarDecl{
	char* first_id;
	char* last_id;
	IdStruct* id;
};

struct _IdStruct{
	IdStruct* next;
	char* id;
};

struct _FuncPart{
	FuncPart* next;

	union{
		FuncDecl* funcDecl;
		FuncDef* funcDef;
		FuncDef2* funcDef2;
	}funcPart;
};

//Function Declaration
struct _FuncDecl{
	char* first_id;
	FuncParams* funcParams;
	char* last_id;
};

struct _FuncDef{
	FuncDecl* funcDecl;
	VarPart* varPart;
	Statements stat;
};

struct _FuncDef2{
	char* id;
	VarPart* varPart;
	Statements stat;
};

struct _FuncParams{
	union{
		Params* params;
		VarParams* varParams;
	}OptionalParams;
};

struct _Params{
	char* first_id;
	char* last_id;
	IdStruct* id;
};

struct _VarParams{
	char* first_id;
	char* last_id;
	IdStruct* id;
};

#endif
