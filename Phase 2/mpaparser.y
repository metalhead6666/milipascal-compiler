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

FuncPart: FuncPartRepeat		
		;

FuncPartRepeat: FuncPartRepeat FuncDeclaration ";"
			  |
			  ;

FuncDeclaration: FuncHeading ";" "forward"
			   | FuncIdent ";" FuncBlock
			   | FuncHeading ";" FuncBlock
			   ;

FuncHeading: "function" ID FormalParamList ":" ID
		   ;

FuncIdent: "function" ID
		 ;		   

FormalParamList: "(" FormalParams FormalParamListRepeat ")"
			   |
			   ;

FormalParamListRepeat: FormalParamListRepeat ";" FormalParams
					 |
					 ;

FormalParams: VarOptional IDList ":" IDList
			;

VarOptional: "var"
		   |
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
	| "if" Expr "then" Stat StatElse
	| "while" Expr "do" Stat
	| "repeat" StatList "until" Expr
	| "val" "(" "paramstr" "(" Expr ")" "," ID ")"
	| StatOptional
	| "writeln" WriteInPList
	;

StatElse: "else" Stat
		|
		;

StatOptional: ID "assign" Expr
			|
			;

WriteInPList: "(" WriteInPListChoose WriteInPListOptional ")"
			|
			;

WriteInPListChoose: Expr
				  | STRING
				  ;

WriteInPListOptional: "," WriteInPListChoose
					|
					;

Expr: Expr ExprOP Expr
	| ExprChoose Expr
	| "(" Expr ")"
	| INTEGER
	| REAL
	| ID ParamList
	;

ExprOP: OP2
	  | OP3
	  | OP4
	  ;

ExprChoose: OP3
		  | NOT
		  ;

ParamList: "(" Expr ParamListOptional ")"
		 |
		 ;

ParamListOptional: "," Expr
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
