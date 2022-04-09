#include <stdio.h>
#include <stdlib.h>
#include "decompiler.h"
#include "hash.h"
#include "semantic.h"

// Declarations
int yylex();
extern char *yytext;
extern FILE *yyin;
extern AST *ast;

int isRunning(void);
int checkSemanticErrors(void);
void initMe(void);
int yyparse();

void compilationSuccessful();

int main(int argc, char **argv)
{
  FILE *file = 0;

  if (!argv[1])
  {
    fprintf(stdout, "\nER: File to compile should be in ARGV 1.");
    fprintf(stdout, "\nCompilation exit. CODE 1.\n");
    exit(1);
  }

  if (!argv[2])
  {
    fprintf(stdout, "\nER: File to decompile should be in ARGV 2.");
    fprintf(stdout, "\nCompilation exit. CODE 1.\n");
    exit(1);
  }

  if (0 == (yyin = fopen(argv[1], "r")))
  {
    fprintf(stdout, "\nER: Cannot read file %s.", argv[1]);
    fprintf(stdout, "\nCompilation exit. CODE 2.\n");
    exit(2);
  }

  initMe();
  yyparse();
  hashPrint();

  if (0 == (file = fopen(argv[2], "w")))
  {
    fprintf(stdout, "\nER: Cannot write on file %s.", argv[2]);
    fprintf(stdout, "\nCompilation exit. CODE 2.\n");
    exit(2);
  }
  decompile(ast, file);

  int semanticErrors = checkSemanticErrors();
  if (semanticErrors)
  {
    fprintf(stdout, "\nER: %d semantic errors.", semanticErrors);
    fprintf(stdout, "\nCompilation exit. CODE 4.\n");
    exit(4);
  }

  compilationSuccessful();
}

void compilationSuccessful()
{
  fprintf(stdout, "\033[0;32m");
  fprintf(stdout, "\nOK: Compilation successful!");
  fprintf(stdout, "\nCompilation exit. CODE 0.\n");
  fprintf(stdout, "\033[0m");
  exit(0);
}
