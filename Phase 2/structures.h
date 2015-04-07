#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef enum{
	Id,
	IntLit, 
	RealLit, 
	String
} Terminals;

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

typedef struct _VarPart VarPart;
typedef struct _Program Program;
typedef struct _FuncDecl FuncDecl;
typedef struct _FuncDef FuncDef;
typedef struct _FuncDef2 FuncDef2;
typedef struct _FuncParams FuncParams;

//Program
struct _Program{
	Terminals id;
	VarPart* varPart;
	union{
		FuncDecl* funcDecl;
		FuncDef* funcDef;
		FuncDef2* funcDef2;
	}funcPart;

};

struct _VarPart{
	Terminals id1;
	Terminals id2;
	Terminals id3;
};


//Function Declaration
struct _FuncDecl{
	Terminals id;
	FuncParams* funcParams;
};

struct _FuncDef{
	//
};

struct _FuncDef2{
	//
};

struct _FuncParams{
	union{
		//
		//
	};
};


#endif
