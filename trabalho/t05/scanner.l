%{
#include "hash.h"
#include "ast.h"
#include "y.tab.h"

int line = 1;
int executing = 1;

int getLineNumber(void) {
    return line;
}

int isRunning(void) {
    return executing;
}
 
%}

%x COMMENT

%%

[\t ]

"\n"                                { ++line; }

char                                {
                                        yylval.symbol = hashInsert(yytext, SYMBOL_KW_CHAR); 
                                        return KW_CHAR;
                                    }

int                                 {
                                        yylval.symbol = hashInsert(yytext, SYMBOL_KW_INT); 
                                        return KW_INT;
                                    }
float                               {
                                        yylval.symbol = hashInsert(yytext, SYMBOL_KW_FLOAT); 
                                        return KW_FLOAT;
                                    }
if                                  {return KW_IF;}
then                                {return KW_THEN;}
else                                {return KW_ELSE;}
while                               {return KW_WHILE;}
goto                                {return KW_GOTO;}
read                                {return KW_READ;}
print                               {return KW_PRINT;}
return                              {return KW_RETURN;}

[0-9]*                              {
                                        yylval.symbol = hashInsert(yytext, SYMBOL_LIT_INTEGER); 
                                        return LIT_INTEGER;
                                    }   

[\,\;\:\(\)\[\]\{\}\+\-\*\/\<\>\=]  {return yytext[0];}

"<="                                {return OPERATOR_LE;}  
">="                                {return OPERATOR_GE;}  
"=="                                {return OPERATOR_EQ;}  
"!="                                {return OPERATOR_DIF;} 

[a-z_\-]+                           {
                                        yylval.symbol = hashInsert(yytext, SYMBOL_TK_IDENTIFIER); 
                                        return TK_IDENTIFIER;
                                    }

'([^'])'                            {
                                        yylval.symbol = hashInsert(yytext, SYMBOL_LIT_CHAR); 
                                        return LIT_CHAR;
                                    }
\"(\\.|[^"\\\n])*\"                 {
                                        yylval.symbol = hashInsert(yytext, SYMBOL_LIT_STRING); 
                                        return LIT_STRING;
                                    }

"\\*"                               { BEGIN(COMMENT); }
<COMMENT>"*\\"                      { BEGIN(INITIAL); }
<COMMENT>"\n"                       { ++line; }
<COMMENT>.
"\\\\".*

.                                   {return TOKEN_ERROR;}

%% 

int yywrap(){
    executing = 0;
    return 1;
}

void initMe(void) {
    line = 1;
    executing = 1;
    hashInit();
}