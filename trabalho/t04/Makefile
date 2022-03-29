#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 3
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa4: lex.yy.o hash.o main.o y.tab.o ast.o semantic.o decompiler.o 
	gcc lex.yy.o hash.o main.o y.tab.o ast.o semantic.o decompiler.o -o etapa4

main.o: main.c
	gcc -c main.c

decompiler.o: decompiler.c
	gcc -c decompiler.c

semantic.o: semantic.c
	gcc -c semantic.c

hash.o: hash.c
	gcc -c hash.c

lex.yy.o: lex.yy.c y.tab.o
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

ast.o: ast.c
	gcc -c ast.c

lex.yy.c: scanner.l
	lex scanner.l

y.tab.c: parser.y
	yacc parser.y -d
	
clean:
	rm lex.yy.c *.o y.tab.* etapa4