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
%type <program> IDList;
%type <program> IDListRepeat;
%type <program> VarDeclaration;
%type <program> funcPart;
%type <program> FuncDeclaration;
%type <program> FuncDeclRepeat;
%type <program> FuncHeading;
%type <program> FormalParamList;
%type <program> FormalParamListRepeat;
%type <program> FormalParams;
%type <program> StatPart;

%union{
	struct Program* program;
	char *string;
};

%%
Prog: ProgHeading ';' ProgBlock '.'         					{program = makeNode("Id", $1, NULL, $3);}
	;

ProgHeading: PROGRAM ID '(' OUTPUT ')'							{$$ = $2;}
		   ;

ProgBlock: varPart funcPart StatPart							{aux = insert_last_brother($2); if(aux != NULL) aux->brother = $3; aux = insert_last_brother($1); if(aux != NULL) aux->brother = $2; $$ = $1;}
		 ;

varPart: VAR VarDeclaration ';' VarDeclarationRepeat			{$$ = makeNode("VarPart", "", $2, $4);}
	   |														{$$ = makeNode("VarPart", "", NULL, NULL);}
	   ;

VarDeclarationRepeat: VarDeclaration ';' VarDeclarationRepeat	{$$ = makeNode("NoPrint", "", $1, $3);}
					|											{$$ = NULL;}
					;		   

VarDeclaration: IDList ':' ID 									{aux = insert_last_brother($1); if(aux != NULL) aux->brother = makeNode("Id", $3, NULL, NULL); $$ = makeNode("VarDecl", "", $1, NULL);}
			  ;		 

IDList: ID IDListRepeat											{$$ = makeNode("Id", $1, NULL, $2);}
	  ;

IDListRepeat: ',' ID IDListRepeat								{$$ = makeNode("Id", $2, NULL, $3);}
	  |															{$$ = NULL;}
	  ;

funcPart: FuncDeclaration ';' FuncDeclRepeat 					{$$ =  makeNode("FuncPart", "", $1, $3);}	
		|														{$$ =  makeNode("FuncPart", "", NULL, NULL);}
		;

FuncDeclRepeat: FuncDeclaration ';' FuncDeclRepeat				{$$ =  makeNode("NoPrint", "", $1, $3);}
			  |													{$$=NULL;}
			  ;

FuncDeclaration: FuncHeading ';' FORWARD						{$$ = makeNode("FuncDecl", "", $1, NULL);}
			   | FUNCTION ID ';' varPart StatPart				{$4->brother = $5; $$ = makeNode("FuncDef2", "", makeNode("Id", $2, NULL, $4), NULL);}
			   | FuncHeading ';' varPart StatPart 				{$3->brother = $4; aux = insert_last_brother($1); aux->brother = $3; $$ = makeNode("FuncDef", "", $1, NULL);}
			   ;

FuncHeading: FUNCTION ID FormalParamList ':' ID 				{aux = insert_last_brother($3); if(aux != NULL) aux->brother = makeNode("Id", $5, NULL, NULL); $$ = makeNode("Id", $2, NULL, $3);}
		   ;		   

FormalParamList: '(' FormalParams FormalParamListRepeat ')'		{$$ = makeNode("FuncParams", "", $2, $3);}
			   |												{$$ = NULL;}
			   ;

FormalParamListRepeat: ';' FormalParams FormalParamListRepeat	{$$ = makeNode("FuncParams", "", $2, $3);}
					 |											{$$ = NULL;}
					 ;

FormalParams: IDList ':' ID 									{aux = insert_last_brother($1); if(aux != NULL) aux->brother = makeNode("Id", $3, NULL, NULL); $$ = makeNode("Params", "", $1, NULL);}
			| VAR IDList ':' ID 								{aux = insert_last_brother($2); if(aux != NULL) aux->brother = makeNode("Id", $4, NULL, NULL); $$ = makeNode("VarParams", "", $2, NULL);}
			;

StatPart: BEG StatList END 										{$$ = makeNode("StatList", "", NULL, NULL);}						
		;

StatList: Stat StatListRepeat									
		;

StatListRepeat: ';' Stat StatListRepeat							
			  |													
			  ;

Stat: StatPart													
	| IF Expr THEN Stat 										
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

Expr: SimpleExpr												
	| SimpleExpr RELATIONALOP SimpleExpr						
	;

SimpleExpr: ADDOP Term
		  | SimpleExpr ADDOP Term
		  | SimpleExpr OR Term
		  | Term
		  ;

Term: Factor
	| Term MULTOP Factor
	;

Factor: '(' Expr ')'											
	  | NOT Factor  											
  	  | INTEGER													
  	  | REAL 													
  	  | ID 														
  	  | ID ParamList 											
  	  ;

ParamList: '(' Expr ParamListOptional ')' 						
		 ;	

ParamListOptional: ',' Expr ParamListOptional 					
				 | 												
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
