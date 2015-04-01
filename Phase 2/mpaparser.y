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
%token OP1
%token OP2
%token OP3
%token OP4
%token ID
%token STRING

%left OP1
%left OP2
%left OP3
%left OP4

%%

Prog: ProgHeading ";" ProgBlock "."
	;

ProgHeading: "program" ID "(output)"
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

StatPart:
		;

FuncPart:
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
