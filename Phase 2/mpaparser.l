%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
	
	int start_line = 1, start_column = 1, count_line = 1, count_column = 1;
%}

%X STATE
%option case-insensitive

reserved (abs|arctan|array|case|char|chr|const|cos|dispose|downto|eof|eoln|exp|file|for|get|goto|in|input|label|ln|maxint|new|nil|odd|of|ord|pack|packed|page|pred|procedure|put|read|readln|record|reset|rewrite|round|set|sin|sqr|sqrt|succ|text|to|trunc|type|unpack|with|write)

%%

"(*"|"{" {BEGIN STATE; start_line = count_line; start_column = count_column; count_column += yyleng;}
<STATE>"*)"|"}" {BEGIN 0; count_column += yyleng;}
<STATE><<EOF>> {printf("Line %d, col %d: unterminated comment\n", start_line, start_column); return *yytext;}
<STATE>"\n" {++count_line; count_column = 1;}
<STATE>. {++count_column;}

{reserved} {count_column += yyleng; yylval.string = (char*)strdup(yytext); return RESERVED;}
[0-9]+((e("+"|"-")?[0-9]+)|("."[0-9]+((e("+"|"-")?)?[0-9]+)?)) {count_column += yyleng; yylval.string = (char*)strdup(yytext); return REAL;}
[0-9]+ {count_column += yyleng; yylval.value = atoi((char*)strdup(yytext)); return INTEGER;}
begin {count_column += yyleng; return BEG;}
do {count_column += yyleng; return DO;}
if {count_column += yyleng; return IF;}
then {count_column += yyleng; return THEN;}
else {count_column += yyleng; return ELSE;}
end {count_column += yyleng; return END;}
forward {count_column += yyleng; return FORWARD;}
function {count_column += yyleng; return FUNCTION;}
output {count_column += yyleng; return OUTPUT;}
paramstr {count_column += yyleng; return PARAMSTR;}
repeat {count_column += yyleng; return REPEAT;}
until {count_column += yyleng; return UNTIL;}
var {count_column += yyleng; return VAR;}
val {count_column += yyleng; return VAL;}
while {count_column += yyleng; return WHILE;}
writeln {count_column += yyleng; return WRITELN;}
program {count_column += yyleng; return PROGRAM;}
":=" {count_column += yyleng; return ASSIGN;}
":"|","|"."|"("|")"|";" {count_column += yyleng; return yytext[0];}

not {count_column += yyleng; return NOT;}
and|"*"|"/"|mod|div {count_column += yyleng; yylval.string = (char*)strdup(yytext); return OP2;}
"+"|"-"|or {count_column += yyleng; yylval.string = (char*)strdup(yytext); return OP3;}
"<"|">"|"="|"<>"|"<="|">=" {count_column += yyleng; yylval.string = (char*)strdup(yytext); return OP4;}

[a-zA-Z][a-zA-Z0-9]* {count_column += yyleng; yylval.string = (char*)strdup(yytext); return ID;}
"'"("''"|[^'\n])*"'" {count_column += yyleng; yylval.string = (char*)strdup(yytext); return STRING;}
"'"([^'\n]*("''")*)* {printf("Line %d, col %d: unterminated string\n", count_line, count_column); count_column += yyleng; return *yytext;}
"\t"|" " {count_column += yyleng;}
"\n" {++count_line; count_column = 1;}
. {printf("Line %d, col %d: illegal character ('%s')\n", count_line, count_column, yytext); count_column += yyleng; return *yytext;}

%%

int yywrap(){
	return 1;
}	
