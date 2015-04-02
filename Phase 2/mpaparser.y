%{
	#include <stdio.h>
	#include <string.h>

	void yyerror(char *s);

	extern char *yytext;
	extern int count_line, count_column;	
%}

%token RESERVED
%token REAL
%token INTEGER
%token NOT
%token OP2
%token OP3
%token OP4
%token ID
%token STRING

%left NOT
%left OP2
%left OP3
%left OP4

%nonassoc IF
%nonassoc "else"

%%

Prog: ProgHeading ";" ProgBlock "."
	;

ProgHeading: "program" ID "(" "output" ")"
		   ;

ProgBlock: VarPart FuncPart StatPart
		 ;

VarPart: "var" VarDeclaration ";" VarDeclarationRepeat
	   |
	   ;

VarDeclarationRepeat: VarDeclarationRepeat VarDeclaration ";"
					|
					;		   

VarDeclaration: IDList ":" ID
			  ;

IDList: ID IDListRepeat
	  ;			 

IDListRepeat: IDListRepeat "," ID
			|
			;

FuncPart: FuncPart FuncDeclaration ";"
		|		
		;

FuncDeclaration: FuncHeading ";" "forward"
			   | "function" ID ";" FuncBlock
			   | FuncHeading ";" FuncBlock
			   ;

FuncHeading: "function" ID FormalParamList ":" ID
		   ;		   

FormalParamList: "(" FormalParams FormalParamListRepeat ")"
			   |
			   ;

FormalParamListRepeat: FormalParamListRepeat ";" FormalParams
					 |
					 ;

FormalParams: "var" IDList ":" ID
			| IDList ":" ID
			;

FuncBlock: VarPart StatPart
		 ;

StatPart: "begin" StatList "end"
		;

StatList: Stat StatListRepeat
		;

StatListRepeat: StatListRepeat ";" Stat
			  |
			  ;

Stat: StatPart
	| "if" Expr "then" Stat %prec IF
	| "if" Expr "then" Stat "else" Stat
	| "while" Expr "do" Stat
	| "repeat" StatList "until" Expr
	| "val" "(" "paramstr" "(" Expr ")" "," ID ")"
	| ID "assign" Expr
	| "writeln" WriteInPList
	|
	;

WriteInPList: "(" Expr WriteInPListOptional ")"
			| "(" STRING WriteInPListOptional ")"
			|
			;

WriteInPListOptional: WriteInPListOptional "," Expr
					| WriteInPListOptional "," STRING
					|
					;

Expr: Expr OP2 Expr
	| Expr OP3 Expr
	| Expr OP4 Expr
	| OP3 Expr
	| NOT Expr	
	| "(" Expr ")"
	| INTEGER
	| REAL
	| ID ParamList
	;

ParamList: "(" Expr ParamListOptional ")"
		 |
		 ;	

ParamListOptional: ParamListOptional "," Expr
				 |
				 ;		 

%%
int main(int argc, char *argv[]){
	if(argc > 0){
		if(strcmp(argv[0], "-t") == 0){
			//print tree here
		}
	}

	return yyparse();
}

void yyerror(char *s){
	printf ("Line %d, col %d: %s: %s\n", count_line, count_column, s, yytext);
}
