#include <stdio.h>
#include <stdlib.h>

// Declarations
void red();
void green();
void reset();
void error();
void finishCompilation();
int yylex();
extern char *yytext;
extern FILE *yyin;
int isRunning(void);
int getLineNumber(void);
void initMe(void);

int main(int argc, char **argv)
{
  FILE *file = 0;
  int token = 0;
  int answer = 0;
  int corrects = 0;
  int tokenNumber = 1;

  if (!argv[1])
  {
    fprintf(stdout, "\nER: File to compile should be in ARGV 1.");
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

  finishCompilation();
}

void finishCompilation()
{
  green();
  fprintf(stdout, "\nOK: Compilation successful!");
  fprintf(stdout, "\nCompilation exit. CODE 0.\n");
  reset();
  exit(0);
}

void red()
{
  printf("\033[1;31m");
}
void green()
{
  printf("\033[0;32m");
}
void reset()
{
  printf("\033[0m");
}
