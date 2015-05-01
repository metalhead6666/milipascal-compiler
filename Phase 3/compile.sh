lex mpasemantic.l 
yacc -v -d mpasemantic.y 
cc -Wall -Wextra -g -o mpasemantic *.c *.h -ll -ly -g
zip mpasemantic.zip mpasemantic.l mpasemantic.y functions.h semantic.h
