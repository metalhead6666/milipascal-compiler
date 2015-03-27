%{
	int start_line = 1, start_column = 1, count_line = 1, count_column = 1;
%}

%X STATE
%option case-insensitive

reserved (abs|arctan|array|case|char|chr|const|cos|dispose|downto|eof|eoln|exp|file|for|get|goto|in|input|label|ln|maxint|new|nil|odd|of|ord|pack|packed|page|pred|procedure|put|read|readln|record|reset|rewrite|round|set|sin|sqr|sqrt|succ|text|to|trunc|type|unpack|with|write)

%%

"(*"|"{" {BEGIN STATE; start_line = count_line; start_column = count_column; count_column += yyleng;}
<STATE>"*)"|"}" {BEGIN 0; count_column += yyleng;}
<STATE><<EOF>> {printf("Line %d, col %d: unterminated comment\n", start_line, start_column); return 0;}
<STATE>"\n" {++count_line; count_column = 1;}
<STATE>. {++count_column;}

{reserved} {printf("RESERVED(%s)\n", yytext); count_column += yyleng;}
[0-9]+((e("+"|"-")?[0-9]+)|("."[0-9]+((e("+"|"-")?)?[0-9]+)?)) {printf("REALLIT(%s)\n", yytext); count_column += yyleng;}
[0-9]+ {printf("INTLIT(%s)\n", yytext); count_column += yyleng;}
begin {printf("BEGIN\n"); count_column += yyleng;}
do {printf("DO\n"); count_column += yyleng;}
if {printf("IF\n"); count_column += yyleng;}
then {printf("THEN\n"); count_column += yyleng;}
else {printf("ELSE\n"); count_column += yyleng;}
end {printf("END\n"); count_column += yyleng;}
forward {printf("FORWARD\n"); count_column += yyleng;}
function {printf("FUNCTION\n"); count_column += yyleng;}
not {printf("NOT\n"); count_column += yyleng;}
output {printf("OUTPUT\n"); count_column += yyleng;}
paramstr {printf("PARAMSTR\n"); count_column += yyleng;}
program {printf("PROGRAM\n"); count_column += yyleng;}
repeat {printf("REPEAT\n"); count_column += yyleng;}
until {printf("UNTIL\n"); count_column += yyleng;}
var {printf("VAR\n"); count_column += yyleng;}
val {printf("VAL\n"); count_column += yyleng;}
while {printf("WHILE\n"); count_column += yyleng;}
writeln {printf("WRITELN\n"); count_column += yyleng;}
":=" {printf("ASSIGN\n"); count_column += yyleng;}
":" {printf("COLON\n"); count_column += yyleng;}
"," {printf("COMMA\n"); count_column += yyleng;}
"." {printf("DOT\n"); count_column += yyleng;}
"(" {printf("LBRAC\n"); count_column += yyleng;}
")" {printf("RBRAC\n"); count_column += yyleng;}
";" {printf("SEMIC\n"); count_column += yyleng;}
and|or {printf("OP1(%s)\n", yytext); count_column += yyleng;}
"<"|">"|"="|"<>"|"<="|">=" {printf("OP2(%s)\n", yytext); count_column += yyleng;}
"+"|"-" {printf("OP3(%s)\n", yytext); count_column += yyleng;}
"*"|"/"|mod|div {printf("OP4(%s)\n", yytext); count_column += yyleng;}
[a-zA-Z][a-zA-Z0-9]* {printf("ID(%s)\n", yytext); count_column += yyleng;}
"'"("''"|[^'\n])*"'" {printf("STRING(%s)\n", yytext); count_column += yyleng;}
"'"([^'\n]*("''")*)* {printf("Line %d, col %d: unterminated string\n", count_line, count_column); count_column += yyleng;}
"\t"|" " {count_column += yyleng;}
"\n" {++count_line; count_column = 1;}
. {printf("Line %d, col %d: illegal character ('%s')\n", count_line, count_column, yytext); count_column += yyleng;}

%%
int main(){
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}
