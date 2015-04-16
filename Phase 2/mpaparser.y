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
%type <statList> StatList;
%type <statList> StatListRepeat;
%type <statList> StatPart;
%type <stat> Stat;
%type <expr> Expr;
%type <writeInPList> WriteInPList;



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
	struct StatList *statList;
	struct Stat *stat;
	struct Expr *expr;
	struct WriteInPList *writeInPList;
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

StatPart: BEG StatList END 										{$$ = $2;}
		;

StatList: Stat StatListRepeat									{$$ = addStatList($1,$2);}				
		;

StatListRepeat: ';' Stat StatListRepeat							{$$ = addStatList($2,$3);}	
			  |													{$$ = NULL;}
			  ;

Stat: StatPart													{$$ = addStat(NULL,NULL,NULL,NULL,$1);}
	| IF Expr THEN Stat 										{$$ = addStat($2,$4,NULL,NULL,NULL);}
	| IF Expr THEN Stat ELSE Stat 								{$$ = $4->next = $6; addStat($2,$4,NULL,NULL,NULL);}
	| WHILE Expr DO Stat 										{$$ = addStat($2,$4,NULL,NULL,NULL);}
	| REPEAT StatList UNTIL Expr 								{$$ = addStat($4,NULL,NULL,NULL,$2);}	
	| VAL '(' PARAMSTR '(' Expr ')' ',' ID ')' 					{$$ = addStat($5,NULL,NULL,$8,NULL);}
	| ID ASSIGN Expr 											{$$ = addStat($3,NULL,NULL,$1,NULL);}
	| WRITELN WriteInPList 										{$$ = addStat(NULL,NULL,$2,NULL,NULL);}
	| 															{$$ = NULL;}
	;

WriteInPList: '(' Optional WriteInPListOptional ')'				{}
			|													{$$ = NULL;}
			;

WriteInPListOptional: ',' Optional WriteInPListOptional
					|
					;

Optional: Expr
		| STRING
		;

Expr: SimpleExpr												{}
	| SimpleExpr RELATIONALOP SimpleExpr						{}
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
			print_tree(program);
		}
	}

	return 0;
}

void yyerror(char *s){
	hasErrors = 1;
	printf("Line %d, col %d: %s: %s\n", count_line, (int)(count_column - strlen(yytext)), s, yytext);
}

