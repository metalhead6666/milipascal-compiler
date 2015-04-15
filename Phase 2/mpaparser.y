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
%right UMINUS UPLUS

%nonassoc THEN
%nonassoc ELSE

%type <string> ProgHeading;
%type <progBlock> ProgBlock;
%type <varPart> varPart;
%type <varPart> VarDeclarationRepeat;
%type <funcPart> funcPart;
%type <idStruct> IDList;
%type <varDecl> VarDeclaration;
%type <funcDeclaration> FuncDeclaration;
%type <funcHeading> FuncHeading;
%type <formalParamList> FormalParamList;
%type <formalParamList> FormalParamListRepeat;
%type <formalParams> FormalParams;

%union{
	struct ProgBlock* progBlock;
	struct VarPart* varPart;
	struct FuncPart* funcPart;
	struct IdStruct* idStruct;
	struct VarDecl* varDecl;
	struct FuncDeclaration* funcDeclaration;
	struct FuncHeading *funcHeading;
	struct FormalParamList *formalParamList;
	struct FormalParams *formalParams;
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

funcPart: FuncDeclaration ';' funcPart  						{$$ = addFuncPart($3, $1);}
		|														{$$ = NULL;}	
		;

FuncDeclaration: FuncHeading ';' FORWARD						{$$ = addFuncDeclaration(NULL,NULL,$1);}
			   | FUNCTION ID ';' varPart StatPart				{$$ = addFuncDeclaration($4,$2,NULL);}
			   | FuncHeading ';' varPart StatPart 				{$$ = addFuncDeclaration($3,NULL,$1);}
			   ;

FuncHeading: FUNCTION ID FormalParamList ':' ID 				{$$ = addFuncHeading($2, $3, $5);}
		   ;		   

FormalParamList: '(' FormalParams FormalParamListRepeat ')'		{$$ = addFormalParamList($2,$3);}
			   |												{$$ = NULL;}
			   ;

FormalParamListRepeat: ';' FormalParams FormalParamListRepeat	{$$ = addFormalParamList($2,$3);}
					 |											{$$ = NULL;}
					 ;

FormalParams: ID IDList ':' ID 									{$$ = addFormalParams($1,$2,$4);}
			| VAR ID IDList ':' ID 								{$$ = addFormalParams($2,$3,$5);}
			;

StatPart: BEG StatList END 										
		;

StatList: StatList ';' Stat
		| Stat 													
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

Expr: Expr OP2 Expr
	| Expr OP3 Expr
	| Expr OP4 Expr
	| '+' Expr %prec UPLUS
	| '-' Expr %prec UMINUS
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

