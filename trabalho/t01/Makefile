#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa1: lex.yy.c
	gcc -o etapa1 lex.yy.c
lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm lex.yy.c etapa1

# #
# # UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
# #
# # Makefile for single compiler call
# # All source files must be included from code embedded in scanner.l
# # In our case, you probably need #include "hash.c" at the beginning
# # and #include "main.c" in the last part of the scanner.l
# #

# etapa1: lex.yy.c
# 	gcc -o etapa1 lex.yy.c
# ${FILENAME}: lex.yy.o hash.o main.o
# 	${CC} -o ${FILENAME} lex.yy.o hash.o
# lex.yy.o: lex.yy.c
# 	gcc lex.yy.c -lfl -o scanner
# # gcc lex.yy.c -lfl
# lex.yy.c: scanner.l
# 	lex scanner.l

# clean:
# 	rm lex.yy.c etapa1
