%{
	#include <string.h>
	#include "functions.h"
	#include "print.h"

	void yyerror(char *s);

	/* values received from lex */
	extern char *yytext;
	extern int count_line, count_column;

	/* node root to print in the tree */
	Program* program;

	/* in case some syntax error appears, doesn't print the AST */
	int hasErrors = 0;
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

%type <string> ProgHeading;
%type <progBlock> ProgBlock;
%type <varPart> varPart;
%type <varPart> VarDeclarationRepeat;
%type <funcPart> funcPart;
%type <idStruct> IDList;
%type <varDecl> VarDeclaration;

%union{
	struct Program* program;
	struct ProgBlock* progBlock;
	struct VarPart* varPart;
	struct FuncPart* funcPart;
	struct IdStruct* idStruct;
	struct VarDecl* varDecl;

	char *string;
};

%%
Prog: ProgHeading ';' ProgBlock '.'         					{program = makeNode($1, $3);}
	;

ProgHeading: PROGRAM ID '(' OUTPUT ')'							{$$ = $2;}
		   ;

ProgBlock: varPart funcPart StatPart							{$$ = addProgBlock($1, $2);}
		 ;

varPart: VAR VarDeclaration ';' VarDeclarationRepeat			{$$ = addVarPart($4, $2);}
	   |														{$$ = NULL;}
	   ;

VarDeclarationRepeat: VarDeclaration ';' VarDeclarationRepeat	{$$ = addVarPart($3, $1);}
					|											{$$ = NULL;}
					;		   

VarDeclaration: ID IDList ':' ID 								{$$ = addVarDecl($1, $4, $2);}
			  ;		 

IDList: ',' ID IDList 											{$$ = addIdStruct($3, $2);}
	  |															{$$ = NULL;}
	  ;

funcPart: funcPart FuncDeclaration ';' 							{/*$$ = addFuncPart_FuncDecl($1, $2);*/}
		|														{$$ = NULL;}	
		;

FuncDeclaration: FuncHeading ';' FORWARD						{/*$$ = $1;*/}
			   | FUNCTION ID ';' varPart StatPart				//
			   | FuncHeading ';' varPart StatPart 				//
			   ;

FuncHeading: FUNCTION ID FormalParamList ':' ID 				{/*$$ = addFuncDecl($2, $3, $5);*/}
		   ;		   

FormalParamList: '(' FormalParams FormalParamListRepeat ')'		//
			   |												{/*$$ = NULL;*/}
			   ;

FormalParamListRepeat: ';' FormalParams FormalParamListRepeat	//
					 |											{/*$$ = NULL;*/}
					 ;

FormalParams: VAR ID IDList ':' ID 								//
			| ID IDList ':' ID 									//
			;

StatPart: BEG StatList END 										{/*$$ = $2;*/}
		;

StatList: StatList ';' Stat 									//
		| Stat 													{/*$$ = $1;*/}
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

WriteInPListOptional: ',' Optional WriteInPListOptional
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

ParamListOptional: ',' Expr ParamListOptional
				 |
				 ;		 

%%
int main(int argc, char **argv){
	yyparse();

	if(argc > 1){
		if(strcmp(argv[1], "-t") == 0 && !hasErrors){
			print_tree(program);
		}
	}

	return 0;
}

void yyerror(char *s){
	hasErrors = 1;
	printf("Line %d, col %d: %s: %s\n", count_line, (int)(count_column - strlen(yytext)), s, yytext);
}
