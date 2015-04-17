lex mpaparser.l 
yacc -v -d mpaparser.y 
cc -o mpaparser *.c *.h -ll -ly -g
zip mpaparser.zip mpaparser.l mpaparser.y functions.c functions.h
