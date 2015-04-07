#ifndef _STRUCTURES_
#define _STRUCTURES_

enum Terminals{
	Id,
	IntLit, 
	RealLit, 
	String
};

enum Operations{
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
};

enum Statements{
	Assign,
	IfElse,
	Repeat,
	StatList,
	ValParam,
	While,
	WriteLn
};

#endif
