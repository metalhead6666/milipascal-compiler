lex mpaparser.l 
yacc -v -d mpaparser.y 
cc -o mpaparser *.c *.h -ll -ly -g
