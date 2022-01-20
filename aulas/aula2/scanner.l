%%

int         {printf("KW TP %s       \n", yytext);}
float       {printf("KW TP %s       \n", yytext);}
char        {printf("KW TP %s       \n", yytext);}
bool        {printf("KW TP %s       \n", yytext);}

for         {printf("KW ST for      \n");}
if          {printf("KW ST if       \n");}
else        {printf("KW ST else     \n");}
while       {printf("KW ST while    \n");}

[0-9]*      {printf("ID Inteiros    \n");}    

[a-zA-Z]+      {printf("ID Random      \n");}

"+"         {printf("OP +");}         
"-"         {printf("OP -");}
"%"         {printf("OP %%");}
"/"         {printf("OP /");}
"^"         {printf("OP ^");}
"*"         {printf("OP *");}

[ \n\t]                                             //Ignores space \n e \t

.           {printf("Error!");}                     //Ignores extra chars

%%

int main(){
    yylex();
}


int yywrap(){
    return 1;
}

