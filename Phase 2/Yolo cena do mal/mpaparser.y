%{
	#include <string.h>
	#include "functions.h"

	void yyerror(char *s);

	/* values received from lex */
	extern char *yytext;
	extern int count_line, count_column;

	/* node root to print in the tree */
	Program* program;
	Program *aux;

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
%token <string> OR
%token <string> MULTOP
%token <string> ADDOP
%token <string> RELATIONALOP
%token <string> ID
%token <string> STRING
%token <string> INTEGER
%token <string> REAL
%token <string> RESERVED

%left ADDOP OR
%left MULTOP
%left NOT

%nonassoc RELATIONALOP
%nonassoc THEN
%nonassoc ELSE

%type <string> ProgHeading;
%type <program> ProgBlock;
%type <program> varPart;
%type <program> VarDeclarationRepeat;
%type <program> funcPart;
%type <program> IDList;
%type <program> VarDeclaration;
%type <program> FuncDeclaration;
%type <program> FuncHeading;
%type <program> FormalParamList;
%type <program> FormalParamListRepeat;
%type <program> FormalParams;
%type <program> StatList;
%type <program> StatListRepeat;
%type <program> StatPart;
%type <program> Stat;
%type <program> Expr;
%type <program> WriteInPList;
%type <program> WriteInPListOptional;
%type <program> Optional;
%type <program> Term;
%type <program> TermRepeat;
%type <program> SimpleExpr;
%type <program> Factor;
%type <program> ParamList;
%type <program> ParamListOptional;

%union{
	struct Program* program;
	char *string;
};

%%
Prog: ProgHeading ';' ProgBlock '.'         					{program = makeNode("Id", $1, $3, NULL);}
	;

ProgHeading: PROGRAM ID '(' OUTPUT ')'							{$$ = $2;}
		   ;

ProgBlock: varPart funcPart StatPart							{$$ = $1;}
		 ;

varPart: VAR VarDeclaration ';' VarDeclarationRepeat			{$$ = makeNode("VarPart", "", $2, $4);}
	   |														{$$ = NULL;}
	   ;

VarDeclarationRepeat: VarDeclaration ';' VarDeclarationRepeat	{$$ = makeNode("VarPart", "", $1, $3);}
					|											{$$ = NULL;}
					;		   

VarDeclaration: ID IDList ':' ID 								{aux = $2; while(aux->brother != NULL) aux = aux->brother; aux->brother = makeNode("Id", $4, NULL, NULL); $$->brother = $2; $$ = makeNode("Id", $1, NULL, $2);}
			  ;		 

IDList: ',' ID IDList 											{$$ = makeNode("Id", $2, NULL, $3);}
	  |															{$$ = NULL;}
	  ;

funcPart: FuncDeclaration ';' funcPart  						{$$ = NULL;}
		|														{$$ = NULL;}	
		;

FuncDeclaration: FuncHeading ';' FORWARD						{$$ = NULL;}
			   | FUNCTION ID ';' varPart StatPart				{$$ = NULL;}
			   | FuncHeading ';' varPart StatPart 				{$$ = NULL;}
			   ;

FuncHeading: FUNCTION ID FormalParamList ':' ID 				{$$ = NULL;}
		   ;		   

FormalParamList: '(' FormalParams FormalParamListRepeat ')'		{$$ = NULL;}
			   |												{$$ = NULL;}
			   ;

FormalParamListRepeat: ';' FormalParams FormalParamListRepeat	{$$ = NULL;}
					 |											{$$ = NULL;}
					 ;

FormalParams: ID IDList ':' ID 									{$$ = NULL;}
			| VAR ID IDList ':' ID 								{$$ = NULL;}
			;

StatPart: BEG StatList END 										{$$ = $2;}
		;

StatList: Stat StatListRepeat									{$$ = NULL;}
		;

StatListRepeat: ';' Stat StatListRepeat							{$$ = NULL;}
			  |													{$$ = NULL;}
			  ;

Stat: StatPart													{$$ = NULL;}
	| IF Expr THEN Stat 										{$$ = NULL;}
	| IF Expr THEN Stat ELSE Stat 								{$$ = NULL;}
	| WHILE Expr DO Stat 										{$$ = NULL;}
	| REPEAT StatList UNTIL Expr 								{$$ = NULL;}
	| VAL '(' PARAMSTR '(' Expr ')' ',' ID ')' 					{$$ = NULL;}
	| ID ASSIGN Expr 											{$$ = NULL;}
	| WRITELN WriteInPList 										{$$ = NULL;}
	| 															{$$ = NULL;}
	;

WriteInPList: '(' Optional WriteInPListOptional ')'				{$$ = NULL;}
			|													{$$ = NULL;}
			;

WriteInPListOptional: ',' Optional WriteInPListOptional 		{$$ = NULL;}
					| 											{$$ = NULL;}
					;

Optional: Expr 													{$$ = NULL;}
		| STRING 												{$$ = NULL;}
		;

Expr: SimpleExpr												{$$ = NULL;}
	| SimpleExpr RELATIONALOP SimpleExpr						{$$ = NULL;}
	;

SimpleExpr: ADDOP Term											{$$ = NULL;}
		  | Term ADDOP SimpleExpr 								{$$ = NULL;}
		  | Term OR SimpleExpr 									{$$ = NULL;}
		  | Term 												{$$ = NULL;}
		  ;

Term: Factor TermRepeat	 										{$$ = NULL;}
	;

TermRepeat: MULTOP Factor TermRepeat							{$$ = NULL;}
		  |														{$$ = NULL;}
		  ;

Factor: '(' Expr ')'											{$$ = NULL;}
	  | NOT Factor  											{$$ = NULL;}
  	  | INTEGER													{$$ = NULL;}
  	  | REAL 													{$$ = NULL;}
  	  | ID 														{$$ = NULL;}
  	  | ID ParamList 											{$$ = NULL;}
  	  ;

ParamList: '(' Expr ParamListOptional ')' 						{$$ = NULL;}
		 ;	

ParamListOptional: ',' Expr ParamListOptional 					{$$ = NULL;}
				 | 												{$$ = NULL;}
				 ;		 


%%
int main(int argc, char **argv){
	yyparse();

	if(argc > 1){
		if(strcmp(argv[1], "-t") == 0 && !hasErrors){
			printf("Program\n");
			print_tree(program, 2);
		}
	}

	return 0;
}

void yyerror(char *s){
	hasErrors = 1;
	printf("Line %d, col %d: %s: %s\n", count_line, (int)(count_column - strlen(yytext)), s, yytext);
}
