%{
	#include "functions.h"
	#include "semantic.h"

	/* function declaration */
	void yyerror(char *s);
	void cannotWriteValues_error(char* type);
	void functionIdentifierExpected_error(Program *p);
	void incompatibleTypeArgument_error(Program *p, int num, char *token, char *type1, char *type2);
	void incompatibleTypeAssigment_error(Program *p, char *token, char *type1, char *type2);
	void incompatibleTypeStatement_error(char *statement, char *type1, char *type2);
	void cannotAppliedType_error(char *token, char *type);
	void cannotAppliedType2_error(char *token, char *type1, char *type2);
	void symbolAlreadyDefined_error(Program *p);
	void symbolNotDefined_error(Program *p);
	void typeIdentifierExpected_error(Program *p);
	void variableIdentifierExpected_error();
	void wrongNumberArguments_error(Program *p, char *token, int type1, int type2);

	/* values received from lex */
	extern char *yytext;
	extern int count_line, count_column;

	/* root node to print in the tree and auxiliars */
	Program *program;
	Program *aux;
	char *aux2;

	/* root node to the symbol table */
	SymbolTableHeader *symbolTableHeader;

	/* in case some syntax error appears, print the AST but not the symbol table */
	int hasErrors = 0;
	int hasErrorsSemantic = 0;
%}

%locations

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
Prog: ProgHeading ';' ProgBlock '.'         					{program = makeNode("Id", $1, NULL, $3, 0 , 0);}
	;

ProgHeading: PROGRAM ID '(' OUTPUT ')'							{$$ = $2;}
		   ;

ProgBlock: varPart funcPart StatPart							{aux = insert_last_brother($2); if(aux != NULL) aux->brother = $3; aux = insert_last_brother($1); if(aux != NULL) aux->brother = $2; $$ = $1;}
		 ;

varPart: VAR VarDeclaration ';' VarDeclarationRepeat			{$$ = makeNode("VarPart", "", $2, $4, 0, 0);}
	   |														{$$ = makeNode("VarPart", "", NULL, NULL, 0, 0);}
	   ;

VarDeclarationRepeat: VarDeclaration ';' VarDeclarationRepeat	{$$ = makeNode("NoPrint", "", $1, $3, 0 , 0);}
					|											{$$ = NULL;}
					;		   

VarDeclaration: IDList ':' ID 									{aux = insert_last_brother($1); if(aux != NULL) aux->brother = makeNode("Id", $3, NULL, NULL, @3.first_line, @3.first_column); $$ = makeNode("VarDecl", "", $1, NULL, 0, 0);}
			  ;		 

IDList: ID IDListRepeat											{$$ = makeNode("Id", $1, NULL, $2, @1.first_line, @1.first_column);}
	  ;

IDListRepeat: ',' ID IDListRepeat								{$$ = makeNode("Id", $2, NULL, $3, @2.first_line, @2.first_column);}
	  |															{$$ = NULL;}
	  ;

funcPart: FuncDeclaration ';' FuncDeclRepeat 					{$$ = makeNode("FuncPart", "", $1, $3, 0, 0);}	
		|														{$$ = makeNode("FuncPart", "", NULL, NULL, 0, 0);}
		;

FuncDeclRepeat: FuncDeclaration ';' FuncDeclRepeat				{$$ = makeNode("NoPrint", "", $1, $3, 0, 0);}
			  |													{$$ = NULL;}
			  ;

FuncDeclaration: FuncHeading ';' FORWARD						{$$ = makeNode("FuncDecl", "", $1, NULL, 0, 0);}
			   | FUNCTION ID ';' varPart StatPart				{aux = insert_last_brother($4); aux->brother = $5; $$ = makeNode("FuncDef2", "", makeNode("Id", $2, NULL, $4, @2.first_line, @2.first_column), NULL, 0, 0);}
			   | FuncHeading ';' varPart StatPart 				{aux = insert_last_brother($3); aux->brother = $4; aux = insert_last_brother($1); aux->brother = $3; $$ = makeNode("FuncDef", "", $1, NULL, 0, 0);}
			   ;

FuncHeading: FUNCTION ID FormalParamList ':' ID 				{aux = insert_last_brother($3); if(aux != NULL) aux->brother = makeNode("Id", $5, NULL, NULL, @5.first_line, @5.first_column); else $3 = makeNode("Id", $5, NULL, NULL, @5.first_line, @5.first_column); $$ = makeNode("Id", $2, NULL, $3, @2.first_line, @2.first_column);}
		   ;		   

FormalParamList: '(' FormalParams FormalParamListRepeat ')'		{$$ = makeNode("FuncParams", "", $2, $3, 0, 0);}
			   |												{$$ = makeNode("FuncParams", "", NULL, NULL, 0, 0);}
			   ;

FormalParamListRepeat: ';' FormalParams FormalParamListRepeat	{$$ = makeNode("NoPrint", "", $2, $3, 0, 0);}
					 |											{$$ = NULL;}
					 ;

FormalParams: IDList ':' ID 									{aux = insert_last_brother($1); if(aux != NULL) aux->brother = makeNode("Id", $3, NULL, NULL, @3.first_line, @3.first_column); else $1 = makeNode("Id", $3, NULL, NULL, @3.first_line, @3.first_column); $$ = makeNode("Params", "", $1, NULL, 0, 0);}
			| VAR IDList ':' ID 								{aux = insert_last_brother($2); if(aux != NULL) aux->brother = makeNode("Id", $4, NULL, NULL, @4.first_line, @4.first_column); else $2 = makeNode("Id", $4, NULL, NULL, @4.first_line, @4.first_column); $$ = makeNode("VarParams", "", $2, NULL, 0, 0);}
			;

StatPart: CompStat												{if($1 == NULL || count_nodes($1) > 1) $$ = makeNode("StatList", "", NULL, NULL, 0, 0); else $$ = $1;}
		;

CompStat: BEG StatList END 										{if(count_nodes($2) > 1) $$ = makeNode("StatList", "", $2, NULL, 0, 0); else $$ = $2;}
		;

StatList: Stat StatListRepeat									{aux = insert_last_brother($1); if(aux != NULL) aux->brother = $2; else $1 = $2; $$ = $1;}
		;

StatListRepeat: ';' Stat StatListRepeat							{aux = insert_last_brother($2); if(aux != NULL) aux->brother = $3; else $2 = $3; $$ = $2;}
			  |													{$$ = NULL;}
			  ;

Stat: CompStat													{$$ = $1;}

	| IF Expr THEN Stat 										{
																	if($4 != NULL){																		
																		$4->brother = makeNode("StatList", "", NULL, NULL, 0, 0);
																		$2->brother = $4;																		
																	}

																	else{
																		$2->brother = makeNode("StatList", "", NULL, makeNode("StatList", "", NULL, NULL, 0, 0), 0, 0);																		
																	}

																	$$ = makeNode("IfElse", "", $2, NULL, 0, 0);
																}

	| IF Expr THEN Stat ELSE Stat 								{
																	if($4 == NULL && $6 == NULL){
																		$2->brother = makeNode("StatList", "", NULL, makeNode("StatList", "", NULL, NULL, 0, 0), 0, 0);
																	}

																	else if($4 == NULL && $6 != NULL){
																		$2->brother = makeNode("StatList", "", NULL, $6, 0, 0);
																	}

																	else if($4 != NULL && $6 == NULL){																		
																		$4->brother =  makeNode("StatList", "", NULL, NULL, 0, 0);
																		$2->brother = $4;
																	}

																	else{																		
																		$4->brother = $6;
																		$2->brother = $4;
																	}

																	$$ = makeNode("IfElse", "", $2, NULL, 0, 0);
																}


	| WHILE Expr DO Stat 										{
																	if($4 == NULL){
																		$2->brother = makeNode("StatList", "", NULL, NULL, 0, 0);
																	}

																	else{
																		$2->brother = $4;
																	}

																	$$ = makeNode("While", "", $2, NULL, 0, 0);
																}

	| REPEAT StatList UNTIL Expr 								{
																	if($2 == NULL){
																		aux = makeNode("StatList", "", NULL, $4, 0, 0);
																		$$ = makeNode("Repeat", "", aux, NULL, 0, 0);
																	}

																	else{
																		if($2->brother != NULL){
																			$2 = makeNode("StatList", "", $2, NULL, 0, 0);
																		}

																		aux = insert_last_brother($2); 
																		aux->brother = $4; 
																		$$ = makeNode("Repeat", "", $2, NULL, 0, 0);
																	}																	
																}

	| VAL '(' PARAMSTR '(' Expr ')' ',' ID ')' 					{aux = insert_last_brother($5); aux->brother = makeNode("Id",$8,NULL,NULL, 0, 0); $$ = makeNode("ValParam", "", aux, NULL, 0, 0);}
	| ID ASSIGN Expr 											{$$ = makeNode("Assign", "", makeNode("Id", $1, NULL, $3, @1.first_line, @1.first_column), NULL, 0, 0);}
	| WRITELN WriteInPList 										{$$ = makeNode("WriteLn", "", $2, NULL, 0, 0);}
	| 															{$$ = NULL;}
	;

WriteInPList: '(' Optional WriteInPListOptional ')'				{aux = insert_last_brother($2); aux->brother = $3; $$ = $2;}
			|													{$$ = NULL;}
			;

WriteInPListOptional: ',' Optional WriteInPListOptional 		{aux = insert_last_brother($2); aux->brother = $3; $$ = $2;}
					| 											{$$ = NULL;}
					;

Optional: Expr 													{$$ = $1;}
		| STRING 												{$$ = makeNode("String", $1, NULL, NULL, 0, 0);}
		;

Expr: SimpleExpr												{$$ = $1;}
	| SimpleExpr RELATIONALOP SimpleExpr						{aux = insert_last_brother($1); aux->brother = $3; aux2=verify_Expr($2); $$ = makeNode(aux2, "", aux, NULL, 0, 0);}
	;

SimpleExpr: ADDOP Term 											{aux2 = verify_SimpleExpr($1, 0); $$ = makeNode(aux2, "", $2, NULL, 0, 0);}
		  | SimpleExpr ADDOP Term								{aux = insert_last_brother($1); aux->brother = $3; aux2 = verify_SimpleExpr($2, 1); $$ = makeNode(aux2, "", aux, NULL, 0, 0);}
		  | SimpleExpr OR Term									{aux = insert_last_brother($1); aux->brother = $3; aux2 = verify_SimpleExpr($2, 2); $$ = makeNode(aux2, "", aux, NULL, 0, 0);}
		  | Term 												{$$ = $1;}
		  ;

Term: Factor													{$$ = $1;}
	| Term MULTOP Factor										{aux = insert_last_brother($1); aux->brother = $3; aux2 = verify_MultOp($2); $$ = makeNode(aux2, "", aux, NULL, 0, 0);}
	;

Factor: '(' Expr ')'											{$$ = $2;}
	  | NOT Factor  											{$$ = makeNode("Not", "", $2, NULL, 0, 0);}
  	  | INTEGER													{$$ = makeNode("IntLit", $1, NULL, NULL, @1.first_line, @1.first_column);}										
  	  | REAL 													{$$ = makeNode("RealLit", $1, NULL, NULL, @1.first_line, @1.first_column);}
  	  | ID 														{$$ = makeNode("Id", $1, NULL, NULL, @1.first_line, @1.first_column);}
  	  | ID ParamList 											{$$ = makeNode("Call", "", makeNode("Id", $1, NULL, $2, @1.first_line, @1.first_column), NULL, 0, 0);}
  	  ;

ParamList: '(' Expr ParamListOptional ')' 						{$2->brother = $3; $$ = $2;}
		 ;	

ParamListOptional: ',' Expr ParamListOptional 					{$2->brother = $3; $$ = $2;}
				 | 												{$$ = NULL;}
				 ;		 


%%
int main(int argc, char **argv){
	int tree = 0, semantic = 0;
	++argv;

	yyparse();

	if(!hasErrors){
		while(--argc){
			if(strcmp(*argv, "-t") == 0){
				tree = 1;
			}
			
			else if(strcmp(*argv, "-s") == 0){
				semantic = 1;
			}
			
			++argv;
		}

		if(tree){
			printf("Program\n");
			print_tree(program, 2);
		}

		if(semantic){
			symbolTableHeader = create_table(program);

			if(!hasErrorsSemantic){
				if(tree){
					printf("\n");
				}

				print_semantic(symbolTableHeader);
			}
		}

		if(!tree && !semantic){
			//printf("AQUI!");
		}
	}

	return 0;
}

void yyerror(char *s){
	hasErrors = 1;
	printf("Line %d, col %d: %s: %s\n", count_line, (int)(count_column - strlen(yytext)), s, yytext);
}

/* error treatment */
void cannotWriteValues_error(char* type){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Cannot write values of type %s\n", count_line, (int)(count_column - strlen(yytext)), type);
	}	
}

void functionIdentifierExpected_error(Program *p){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Function identifier expected\n", p->line, p->column);	
	}
}

void incompatibleTypeArgument_error(Program *p, int num, char *token, char *type1, char *type2){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Incompatible type for argument %d in call to function %s (got %s, expected %s)\n", p->line, p->column, num, token, type1, type2);
	}
}

void incompatibleTypeAssigment_error(Program *p, char *token, char *type1, char *type2){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Incompatible type in assigment to %s (got %s, expected %s)\n", p->line, p->column, token, type1, type2);
	}
}

void incompatibleTypeStatement_error(char *statement, char *type1, char *type2){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Incompatible type in %s statement (got %s, expected %s)\n", count_line, (int)(count_column - strlen(yytext)), statement, type1, type2);
	}
}

void cannotAppliedType_error(char *token, char *type){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Operator %s cannot be applied to type %s\n", count_line, (int)(count_column - strlen(yytext)), token, type);
	}
}

void cannotAppliedType2_error(char *token, char *type1, char *type2){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", count_line, (int)(count_column - strlen(yytext)), token, type1, type2);
	}
}

void symbolAlreadyDefined_error(Program *p){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Symbol %s already defined\n", p->line, p->column, p->value);
	}
}

void symbolNotDefined_error(Program *p){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Symbol %s not defined\n", p->line, p->column, p->value);
	}
}

void typeIdentifierExpected_error(Program *p){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Type identifier expected\n",  p->line, p->column);
	}
}

void variableIdentifierExpected_error(){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Variable identifier expected\n", count_line, (int)(count_column - strlen(yytext)));
	}
}

void wrongNumberArguments_error(Program *p, char *token, int type1, int type2){
	if(!hasErrorsSemantic){
		hasErrorsSemantic = 1;
		printf("Line %d, col %d: Wrong number of arguments in call to function %s (got %d, expected %d)\n", p->line, p->column, token, type1, type2);
	}
}
