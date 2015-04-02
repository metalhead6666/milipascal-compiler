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
%token START
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
%token OP2
%token OP3
%token OP4
%token ID
%token STRING

%left NOT
%left OP2
%left OP3
%left OP4

%nonassoc IFX
%nonassoc ELSE

%%

Prog: ProgHeading ';' ProgBlock '.'
	;

ProgHeading: PROGRAM ID '(' OUTPUT ')'
		   ;

ProgBlock: VarPart FuncPart StatPart
		 ;

VarPart: VAR VarDeclaration ';' VarDeclarationRepeat
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

FuncPart: FuncPart FuncDeclaration ';'
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

FuncBlock: VarPart StatPart
		 ;

StatPart: START StatList END
		;

StatList: Stat StatListRepeat
		;

StatListRepeat: StatListRepeat ";" Stat
			  |
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
			//print tree here
		}
	}

	return yyparse();
}

void yyerror(char *s){
	printf ("Line %d, col %d: %s: %s\n", count_line, count_column, s, yytext);
}
