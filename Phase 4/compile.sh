lex mpacompiler.l 
yacc -v -d mpacompiler.y 
cc -Wall -Wextra -g -o mpacompiler *.c *.h -ll -ly -g
zip mpacompiler.zip mpacompiler.l mpacompiler.y functions.h semantic.h generator.h
