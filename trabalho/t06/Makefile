#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 3
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa6: lex.yy.o hash.o main.o y.tab.o ast.o semantic.o decompiler.o tacs.o 
	gcc -Wall lex.yy.o hash.o main.o y.tab.o ast.o semantic.o decompiler.o tacs.o -o etapa6

main.o: main.c
	gcc -Wall -c main.c

decompiler.o: decompiler.c
	gcc -Wall -c decompiler.c

tacs.o: tacs.c
	gcc -c tacs.c

semantic.o: semantic.c
	gcc -Wall -c semantic.c

hash.o: hash.c
	gcc -Wall -c hash.c

lex.yy.o: lex.yy.c y.tab.o
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -Wall -c y.tab.c

ast.o: ast.c
	gcc -Wall -c ast.c

lex.yy.c: scanner.l
	lex scanner.l

y.tab.c: parser.y
	yacc parser.y -d
	
clean:
	rm lex.yy.c *.o y.tab.* a.out out.s out.txt etapa6