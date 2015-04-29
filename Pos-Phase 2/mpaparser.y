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
	char *aux2;

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
%type <program> CompStat;
%type <program> StatList;
%type <program> StatListRepeat;
%type <program> Stat;
%type <program> Expr;
%type <program> SimpleExpr;
%type <program> Factor;
%type <program> Term;
%type <program> WriteInPList;
%type <program> WriteInPListOptional;
%type <program> Optional;
%type <program> ParamList;
%type <program> ParamListOptional;

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

funcPart: FuncDeclaration ';' FuncDeclRepeat 					{$$ = makeNode("FuncPart", "", $1, $3);}	
		|														{$$ = makeNode("FuncPart", "", NULL, NULL);}
		;

FuncDeclRepeat: FuncDeclaration ';' FuncDeclRepeat				{$$ = makeNode("NoPrint", "", $1, $3);}
			  |													{$$ = NULL;}
			  ;

FuncDeclaration: FuncHeading ';' FORWARD						{$$ = makeNode("FuncDecl", "", $1, NULL);}
			   | FUNCTION ID ';' varPart StatPart				{aux = insert_last_brother($4); aux->brother = $5; $$ = makeNode("FuncDef2", "", makeNode("Id", $2, NULL, $4), NULL);}
			   | FuncHeading ';' varPart StatPart 				{aux = insert_last_brother($3); aux->brother = $4; aux = insert_last_brother($1); aux->brother = $3; $$ = makeNode("FuncDef", "", $1, NULL);}
			   ;

FuncHeading: FUNCTION ID FormalParamList ':' ID 				{aux = insert_last_brother($3); if(aux != NULL) aux->brother = makeNode("Id", $5, NULL, NULL); else $3 = makeNode("Id", $5, NULL, NULL); $$ = makeNode("Id", $2, NULL, $3);}
		   ;		   

FormalParamList: '(' FormalParams FormalParamListRepeat ')'		{$$ = makeNode("FuncParams", "", $2, $3);}
			   |												{$$ = makeNode("FuncParams", "", NULL, NULL);}
			   ;

FormalParamListRepeat: ';' FormalParams FormalParamListRepeat	{$$ = makeNode("FuncParams", "", $2, $3);}
					 |											{$$ = NULL;}
					 ;

FormalParams: IDList ':' ID 									{aux = insert_last_brother($1); if(aux != NULL) aux->brother = makeNode("Id", $3, NULL, NULL); else $1 = makeNode("Id", $3, NULL, NULL); $$ = makeNode("Params", "", $1, NULL);}
			| VAR IDList ':' ID 								{aux = insert_last_brother($2); if(aux != NULL) aux->brother = makeNode("Id", $4, NULL, NULL); else $2 = makeNode("Id", $4, NULL, NULL); $$ = makeNode("VarParams", "", $2, NULL);}
			;

StatPart: CompStat												{if($1 == NULL || count_nodes($1) > 1) $$ = makeNode("StatList", "", NULL, NULL); else $$ = $1;}
		;

CompStat: BEG StatList END 										{$$ = makeNode("StatList", "", $2, NULL);}
		;

StatList: Stat StatListRepeat									{aux = insert_last_brother($1); if(aux != NULL) aux->brother = $2; $$ = makeNode("NoPrint", "", NULL, $1);}
		;

StatListRepeat: ';' Stat StatListRepeat							{aux = insert_last_brother($2); if(aux != NULL) aux->brother = $3; $$ = makeNode("NoPrint", "", NULL, $2);}
			  |													{$$ = NULL;}
			  ;

Stat: CompStat													{$$ = $1;}

	| IF Expr THEN Stat 										{
																	if($4!=NULL){																		
																		$4->brother = makeNode("StatList", "", NULL, NULL);
																		$2->brother = $4;
																		$$ = makeNode("IfElse", "", $2, NULL);
																	}
																	else{
																		$2->brother = makeNode("StatList", "", NULL, makeNode("StatList", "", NULL, NULL));
																		$$ = makeNode("IfElse", "", $2, NULL);
																	}
																}

	| IF Expr THEN Stat ELSE Stat 								{
																	if($4==NULL && $6==NULL){
																		$2->brother = makeNode("StatList", "", NULL, makeNode("StatList", "", NULL, NULL));
																	}
																	else if($4==NULL && $6!=NULL){
																		$2->brother = makeNode("StatList", "", NULL, $6);
																	}
																	else if($4!=NULL && $6==NULL){																		
																		$4->brother =  makeNode("StatList", "", NULL, NULL);
																		$2->brother = $4;
																	}
																	else{																		
																		$4->brother = $6;
																		$2->brother = $4;
																	}
																	$$ = makeNode("IfElse", "", $2, NULL);
																}


	| WHILE Expr DO Stat 										{
																	if($4==NULL){
																		$2->brother = makeNode("StatList", "", NULL, NULL);
																	}
																	else{
																		$2->brother = $4;
																	}
																	$$ = makeNode("While", "", $2, NULL);
																}

	| REPEAT StatList UNTIL Expr 								{
																	if($2==NULL){
																		aux = makeNode("StatList", "", NULL, NULL);
																		$$ = makeNode("Repeat", "", aux, NULL);
																	}
																	else{
																		if($2->brother!=NULL){
																			aux = insert_last_brother($2); 
																			aux->brother = $4; 
																			$$ = makeNode("Repeat", "", $2, NULL);
																		}
																		else{
																			aux = makeNode("StatList", "", NULL, NULL);
																			aux->brother = $4; 
																			$$ = makeNode("Repeat", "", aux, NULL);
																		}
																	}																	
																}

	| VAL '(' PARAMSTR '(' Expr ')' ',' ID ')' 					{aux = insert_last_brother($5); aux->brother = makeNode("Id",$8,NULL,NULL); $$ = makeNode("ValParam", "", aux, NULL);}
	| ID ASSIGN Expr 											{$$ = makeNode("Assign", "", makeNode("Id", $1, NULL, $3), NULL);}
	| WRITELN WriteInPList 										{$$ = makeNode("WriteLn", "", $2, NULL);}
	| 															{$$ = NULL;}
	;

WriteInPList: '(' Optional WriteInPListOptional ')'				{aux = insert_last_brother($2); aux->brother = $3; $$ = makeNode("NoPrint", "", NULL, aux);}
			|													{$$ = NULL;}
			;

WriteInPListOptional: ',' Optional WriteInPListOptional 		{aux = insert_last_brother($2); aux->brother = $3; $$ = makeNode("NoPrint", "", NULL, aux);}
					| 											{$$ = NULL;}
					;

Optional: Expr 													{$$ = $1;}
		| STRING 												{$$ = makeNode("String", $1, NULL, NULL);}
		;

Expr: SimpleExpr												{$$ = $1;}
	| SimpleExpr RELATIONALOP SimpleExpr						{aux = insert_last_brother($1); aux->brother=$3; aux2=verify_Expr($2); $$=makeNode(aux2, "", aux, NULL);}
	;

SimpleExpr: ADDOP Term 											{aux2 = verify_SimpleExpr($1,0); $$ = makeNode(aux2, "", $2, NULL);}
		  | SimpleExpr ADDOP Term								{aux = insert_last_brother($1); aux->brother=$3; aux2 = verify_SimpleExpr($2,1); $$ = makeNode(aux2, "", aux, NULL);}
		  | SimpleExpr OR Term									{aux = insert_last_brother($1); aux->brother=$3; aux2 = verify_SimpleExpr($2,2); $$ = makeNode(aux2, "", aux, NULL);}
		  | Term 												{$$ = $1;}
		  ;

Term: Factor													{$$ = $1;}
	| Term MULTOP Factor										{aux = insert_last_brother($1); aux->brother = $3; aux2 = verify_MultOp($2); $$ = makeNode(aux2, "", aux, NULL);}
	;

Factor: '(' Expr ')'											{$$ = $2;}
	  | NOT Factor  											{$$ = makeNode("Not", "", $2, NULL);}
  	  | INTEGER													{$$ = makeNode("IntLit", $1, NULL, NULL);}										
  	  | REAL 													{$$ = makeNode("RealLit", $1, NULL, NULL);}
  	  | ID 														{$$ = makeNode("Id", $1, NULL, NULL);}
  	  | ID ParamList 											{$$ = makeNode("Call", "", makeNode("Id", $1, NULL, $2), NULL);}
  	  ;

ParamList: '(' Expr ParamListOptional ')' 						{$2->brother = $3; $$ = makeNode("NoPrint", "", NULL, $2);}
		 ;	

ParamListOptional: ',' Expr ParamListOptional 					{$2->brother = $3; $$ = makeNode("NoPrint", "", NULL, $2);}
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

