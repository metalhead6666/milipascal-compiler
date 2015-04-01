%{
	#include "y.tab.h"
	
	int start_line = 1, start_column = 1, count_line = 1, count_column = 1;
%}

%X STATE
%option case-insensitive

tokens (begin|do|if|then|else|end|forward|function|output|paramstr|program|repeat|until|var|val|while|writeln|":="|":"|","|"."|"("|")"|";")
reserved (abs|arctan|array|case|char|chr|const|cos|dispose|downto|eof|eoln|exp|file|for|get|goto|in|input|label|ln|maxint|new|nil|odd|of|ord|pack|packed|page|pred|procedure|put|read|readln|record|reset|rewrite|round|set|sin|sqr|sqrt|succ|text|to|trunc|type|unpack|with|write)

%%

"(*"|"{" {BEGIN STATE; start_line = count_line; start_column = count_column; count_column += yyleng;}
<STATE>"*)"|"}" {BEGIN 0; count_column += yyleng;}
<STATE><<EOF>> {printf("Line %d, col %d: unterminated comment\n", start_line, start_column); return *yytext;}
<STATE>"\n" {++count_line; count_column = 1;}
<STATE>. {++count_column;}

{reserved} {count_column += yyleng; return RESERVED;}
[0-9]+((e("+"|"-")?[0-9]+)|("."[0-9]+((e("+"|"-")?)?[0-9]+)?)) {count_column += yyleng; return REAL;}
[0-9]+ {count_column += yyleng; return INTEGER;}
tokens {count_column += yyleng; return *yytext;}

not {count_column += yyleng; return OP1;}
and|"*"|"/"|mod|div {count_column += yyleng; return OP2;}
"+"|"-"|or {count_column += yyleng; return OP3;}
"<"|">"|"="|"<>"|"<="|">=" {count_column += yyleng; return OP4;}

[a-zA-Z][a-zA-Z0-9]* {count_column += yyleng; return ID;}
"'"("''"|[^'\n])*"'" {count_column += yyleng; return STRING;}
"'"([^'\n]*("''")*)* {printf("Line %d, col %d: unterminated string\n", count_line, count_column); count_column += yyleng;}
"\t"|" " {count_column += yyleng;}
"\n" {++count_line; count_column = 1;}
. {printf("Line %d, col %d: illegal character ('%s')\n", count_line, count_column, yytext); count_column += yyleng;}

%%
int yywrap(){
	return 1;
}	
