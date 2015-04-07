%{
	#include <stdio.h>
	#include <string.h>
	#include "functions.h"

	void yyerror(char *s);

	extern char *yytext;
	extern int count_line, count_column;	
%}

%union{
	struct _Program* program;
	struct _VarPart* varPart;
	struct _VarDecl* varDecl;
	struct _IdStruct* ids;
	struct _FuncPart* funcPart;
	struct _FuncDecl* funcDecl;
	struct _FuncDef* funcDef;
	struct _FuncDef2* funcDef2;
	struct _FuncParams* funcParams;
	struct _Params* params;
	struct _VarParams* varParams;
	Terminals type;
	Operators ops;

	char *string;
	int value;
}

%token <string> RESERVED
%token <string> REAL
%token <value> INTEGER
%token BEG
%token DO
%token IF
%token THEN
%token ELSE
%token END
%token FORWARD
%token FUNCTION
%token OUTPUT
%token PARAMSTR
%token REPEAT
%token UNTIL
%token VAR
%token VAL
%token WHILE
%token WRITELN
%token PROGRAM
%token ASSIGN
%token NOT
%token <string> OP2
%token <string> OP3
%token <string> OP4
%token <string> ID
%token <string> STRING

%left NOT
%left OP2
%left OP3
%left OP4

%nonassoc IFX
%nonassoc ELSE

%type <program> Prog;

%%

Prog: ProgHeading ';' ProgBlock '.'         {}//program=makeNode($1,$3);}
	;

ProgHeading: PROGRAM ID '(' OUTPUT ')'
		   ;

ProgBlock: varPart funcPart StatPart
		 ;

varPart: VAR VarDeclaration ';' VarDeclarationRepeat
	   |
	   ;

VarDeclarationRepeat: VarDeclarationRepeat VarDeclaration ';'
					|
					;		   

VarDeclaration: IDList ':' ID
			  ;

IDList: ID IDListRepeat
	  ;			 

IDListRepeat: IDListRepeat ',' ID
			|
			;

funcPart: funcPart FuncDeclaration ';'
		|		
		;

FuncDeclaration: FuncHeading ';' FORWARD
			   | FUNCTION ID ';' FuncBlock
			   | FuncHeading ';' FuncBlock
			   ;

FuncHeading: FUNCTION ID FormalParamList ':' ID
		   ;		   

FormalParamList: '(' FormalParams FormalParamListRepeat ')'
			   |
			   ;

FormalParamListRepeat: FormalParamListRepeat ';' FormalParams
					 |
					 ;

FormalParams: VAR IDList ':' ID
			| IDList ':' ID
			;

FuncBlock: varPart StatPart
		 ;

StatPart: BEG StatList END
		;

StatList: StatList ';' Stat
		| Stat
		;

Stat: StatPart
	| IF Expr THEN Stat %prec IFX
	| IF Expr THEN Stat ELSE Stat
	| WHILE Expr DO Stat
	| REPEAT StatList UNTIL Expr
	| VAL '(' PARAMSTR '(' Expr ')' ',' ID ')'
	| ID ASSIGN Expr
	| WRITELN WriteInPList
	|
	;

WriteInPList: '(' Expr WriteInPListOptional ')'
			| '(' STRING WriteInPListOptional ')'
			|
			;

WriteInPListOptional: WriteInPListOptional ',' Expr
					| WriteInPListOptional ',' STRING
					|
					;

Expr: Expr OP2 Expr
	| Expr OP3 Expr
	| Expr OP4 Expr
	| OP3 Expr
	| NOT Expr	
	| '(' Expr ')'
	| INTEGER
	| REAL
	| ID ParamList
	;

ParamList: '(' Expr ParamListOptional ')'
		 |
		 ;	

ParamListOptional: ParamListOptional ',' Expr
				 |
				 ;		 

%%
int main(int argc, char *argv[]){
	if(argc > 0){
		if(strcmp(argv[0], "-t") == 0){
			print_tree();
		}
	}

	return yyparse();
}

void yyerror(char *s){
	printf ("Line %d, col %d: %s: %s\n", count_line, count_column, s, yytext);
}
