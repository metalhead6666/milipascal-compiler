lex mpaparser.l 
yacc -v -d mpaparser.y 
cc -o mpaparser *.c *.h -ll -ly -g
zip mpaparser.zip mpaparser.l mpaparser.y structures.h functions.c functions.h
