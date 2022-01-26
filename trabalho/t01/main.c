#include <stdio.h>
#include <stdlib.h>

//lex.yy.h
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

  if (0 == (yyin = fopen(argv[1], "r")))
  {
    printf("Cannot open file %s... \n", argv[1]);
    exit(1);
  }

  if (0 == (file = fopen(argv[2], "r")))
  {
    printf("Cannot open file %s... \n", argv[2]);
    exit(1);
  }

  initMe();
  while (isRunning())
  {
    token = yylex();

    if (!isRunning())
      break;

    fscanf(file, "%d", &answer);
    if (token == answer)
    {
      fprintf(stderr, "\n   ok = %d  \t| %d = %d \t| Line %d \t| %s", tokenNumber, token, answer, getLineNumber(), yytext);
      ++corrects;
    }
    else
      fprintf(stderr, "\nERROR = %d  \t| %d = %d \t| Line %d \t| %s", tokenNumber, token, answer, getLineNumber(), yytext);
    ++tokenNumber;
  }
  fprintf(stderr, "\n\nCorrects: %d | Errors: %d\n\n", corrects, tokenNumber - corrects - 1);

  hashPrint();
}
