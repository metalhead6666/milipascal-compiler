%{
	#include "functions.h"
	#include "print.h"

	void yyerror(char *s);

	extern char *yytext;
	extern int count_line, count_column;

	Program* program;
%}

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
%token <string> INTEGER
%token <string> REAL
%token <string> RESERVED

%left OP4
%left OP3
%left OP2
%left NOT

%nonassoc IFX
%nonassoc ELSE

%type <program> Prog;
%type <string> ProgHeading;
%type <progBlock> ProgBlock;
%type <varPart> varPart;
%type <funcPart> funcPart;

%union{
	struct Program* program;
	struct ProgBlock* progBlock;
	struct VarPart* varPart;
	struct FuncPart* funcPart;

	char *string;
};

%%
Prog: ProgHeading ';' ProgBlock '.'         					{program = makeNode($1, $3);}
	;

ProgHeading: PROGRAM ID '(' OUTPUT ')'							{$$ = $2;}
		   ;

ProgBlock: varPart funcPart StatPart							{$$ = addProgBlock($1, $2);}
		 ;

varPart: VAR VarDeclaration ';' VarDeclarationRepeat			{$$ = NULL;}
	   |														{$$ = NULL;}
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
		|														{$$ = NULL;}	
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

WriteInPList: '(' Optional WriteInPListOptional ')'
			|
			;

WriteInPListOptional: WriteInPListOptional ',' Optional
					|
					;

Optional: Expr
		| STRING
		;					

Expr: Expr OP2 Expr
	| Expr OP3 Expr
	| Expr OP4 Expr
	| '+' Expr %prec NOT
	| '-' Expr %prec NOT
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
int main(int argc, char **argv){
	yyparse();

	if(argc > 1){
		if(strcmp(argv[1], "-t") == 0){
			print_tree(program);
		}
	}

	return 0;
}

void yyerror(char *s){
	printf("Line %d, col %d: %s: %s\n", count_line, count_column, s, yytext);
}
