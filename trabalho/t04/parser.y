%{
    #include "ast.h"
    #include "hash.h"
    #include "semantic.h"

    int getLineNumber();

    AST* ast = NULL;
%}

%union{
    HASH_NODE *symbol;
    AST *ast;
}

%token<symbol> KW_CHAR
%token<symbol> KW_INT
%token<symbol> KW_FLOAT
%token<symbol> KW_READ
%token<symbol> TK_IDENTIFIER
%token<symbol> LIT_INTEGER
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_GOTO
%token KW_PRINT
%token KW_RETURN
%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token TOKEN_ERROR

%type<ast> expression
%type<ast> command
%type<ast> listOfCommands
%type<ast> optionalNextCommand
%type<ast> attribuitionCommand
%type<ast> label
%type<ast> listOfExpressions
%type<ast> nextExpressions
%type<ast> printCommand
%type<ast> printExpression
%type<ast> listToPrint
%type<ast> nextToPrint
%type<ast> returnCommand
%type<ast> gotoCommand
%type<ast> ifCommand
%type<ast> elseCommand
%type<ast> whileCommand
%type<ast> functionDeclaration
%type<ast> parameter
%type<ast> parameterList
%type<ast> nextParameter
%type<ast> declaration
%type<ast> listOfDeclarations
%type<ast> programa
%type<ast> varDeclaration
%type<ast> singleLiteral
%type<ast> vectorDeclaration
%type<ast> singleLiteralSequence
%type<ast> vectorInitializationList

%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF '<' '>' 
%left '+' '-'
%left '*' '/'

%{
    int yylex();
    int yyerror();
    void rootFunctions(AST* node){
        // astPrint(node, 0);
        check_and_set_declaration(node);
        check_undeclared();
        check_operands(node);
    }
%}

%%

programa: 
    listOfDeclarations                                                          { 
                                                                                    $$ = $1; ast = $$;
                                                                                    rootFunctions($$);
                                                                                }
    ;

listOfDeclarations: 
    declaration listOfDeclarations                                              { $$ = branchUp(AST_LDEC, $1, $2, 0, 0, 0); }
    |                                                                           { $$ = 0; }
    ;

declaration: 
    varDeclaration                                                              { $$ = $1; }
    | vectorDeclaration                                                         { $$ = $1; }
    | functionDeclaration                                                       { $$ = $1; }
    ;

singleLiteral: 
    LIT_INTEGER                                                                 { $$ = symbolize($1); }
    | LIT_CHAR                                                                  { $$ = symbolize($1); }
    ;

varDeclaration:
    KW_INT TK_IDENTIFIER ':' singleLiteral ';'                                  { $$ = branchUp(AST_VAR_I, symbolize($1), symbolize($2), $4, 0, 0); }
    | KW_CHAR TK_IDENTIFIER ':' singleLiteral ';'                               { $$ = branchUp(AST_VAR_C, symbolize($1), symbolize($2), $4, 0, 0); }
    | KW_FLOAT TK_IDENTIFIER ':' LIT_INTEGER '/' LIT_INTEGER ';'                { $$ = branchUp(AST_VAR_F, symbolize($1), symbolize($2), symbolize($4), symbolize($6), 0); }
    ;

vectorDeclaration:
    KW_INT TK_IDENTIFIER '[' singleLiteral ']' vectorInitializationList         { $$ = branchUp(AST_VECT_I, symbolize($1), symbolize($2), $4, $6, 0); }
    | KW_CHAR TK_IDENTIFIER '[' singleLiteral ']' vectorInitializationList      { $$ = branchUp(AST_VECT_C, symbolize($1), symbolize($2), $4, $6, 0); }
    | KW_FLOAT TK_IDENTIFIER '[' singleLiteral ']' vectorInitializationList     { $$ = branchUp(AST_VECT_F, symbolize($1), symbolize($2), $4, $6, 0); }
    ;

vectorInitializationList:
    ':' singleLiteralSequence ';'                                               { $$ = branchUp(AST_LITS_STRT, $2, 0, 0, 0, 0); }
    | ';'                                                                       { $$ = 0; }
    ;

singleLiteralSequence: 
    singleLiteral singleLiteralSequence                                         { $$ = branchUp(AST_LITS_NEXT, $1, $2, 0, 0, 0); }
    | singleLiteral                                                             { $$ = $1; }
    ;

functionDeclaration:
    KW_INT TK_IDENTIFIER '(' parameterList ')' command                          { $$ = branchUp(AST_FUNC_I, symbolize($1), symbolize($2), $4, $6, 0); }
    | KW_CHAR TK_IDENTIFIER '(' parameterList ')' command                       { $$ = branchUp(AST_FUNC_C, symbolize($1), symbolize($2), $4, $6, 0); }
    | KW_FLOAT TK_IDENTIFIER '(' parameterList ')' command                      { $$ = branchUp(AST_FUNC_F, symbolize($1), symbolize($2), $4, $6, 0); }
    ;
 
parameterList: 
    parameter nextParameter                                                     { $$ = branchUp(AST_PARA_START, $1, $2, 0, 0, 0); }
    |                                                                           { $$ = 0; }
    ;
    
nextParameter:
    ',' parameter nextParameter                                                 { $$ = branchUp(AST_PARA_NEXT, $2, $3, 0, 0, 0); }
    |                                                                           { $$ = 0; }
    ;

parameter:
    KW_INT     TK_IDENTIFIER                                                    { $$ = branchUp(AST_PARA_I, symbolize($1), symbolize($2), 0, 0, 0); }
    | KW_CHAR  TK_IDENTIFIER                                                    { $$ = branchUp(AST_PARA_C, symbolize($1), symbolize($2), 0, 0, 0); }
    | KW_FLOAT TK_IDENTIFIER                                                    { $$ = branchUp(AST_PARA_F, symbolize($1), symbolize($2), 0, 0, 0); }
    ; 

listOfCommands: 
    command ';' optionalNextCommand                                             { $$ = branchUp(AST_LCMD, $1, $3, 0, 0, 0); }
    | label ':' optionalNextCommand                                             { $$ = branchUp(AST_LBEL, $1, $3, 0, 0, 0); }
    ;

optionalNextCommand:
    listOfCommands                                                              { $$ = $1; }
    |                                                                           { $$ = 0; }
    ;

label:
    TK_IDENTIFIER                                                               { $$ = symbolize($1);  }
    ;
    
command: 
    '{' '}'                                                                     { $$ = branchUp(AST_LCMD_CURL, 0, 0, 0, 0, 0); }
    | '{' listOfCommands '}'                                                    { $$ = branchUp(AST_LCMD_CURL, $2, 0, 0, 0, 0); }
    | attribuitionCommand                                                       { $$ = $1; }
    | printCommand                                                              { $$ = $1; }
    | returnCommand                                                             { $$ = $1; }
    | ifCommand                                                                 { $$ = $1; }
    | elseCommand                                                               { $$ = $1; }
    | whileCommand                                                              { $$ = $1; }
    | gotoCommand                                                               { $$ = $1; }
    |                                                                           { $$ = 0; }
    ;

attribuitionCommand:    
    TK_IDENTIFIER '=' expression                                                { $$ = branchUp(AST_ATTR, symbolize($1), $3, 0, 0, 0); }
    | TK_IDENTIFIER '[' expression ']' '=' expression                           { $$ = branchUp(AST_ATTR_VEC, symbolize($1), $3, $6, 0, 0); }
    ;

printCommand:
    KW_PRINT listToPrint                                                        { $$ = branchUp(AST_PRNT_START, $2, 0, 0, 0, 0); }
    ;

listToPrint:
    printExpression nextToPrint                                                 { $$ = branchUp(AST_PRNT_FIRST, $1, $2, 0, 0, 0); }
    ;

nextToPrint: 
    ',' printExpression nextToPrint                                             { $$ = branchUp(AST_PRNT_NEXT, $2, $3, 0, 0, 0); }
    |                                                                           { $$ = 0; }
    ;

printExpression:
    LIT_STRING                                                                  { $$ = symbolize($1); }
    | expression                                                                { $$ = $1; }

returnCommand:
    KW_RETURN expression                                                        { $$ = branchUp(AST_RTRN, $2, 0, 0, 0, 0); }
    ;

ifCommand:
    KW_IF expression KW_THEN command                                            { $$ = branchUp(AST_IF, $2, $4, 0, 0, 0); }
    ;

elseCommand:
    KW_IF expression KW_THEN command KW_ELSE command                            { $$ = branchUp(AST_ELSE, $2, $4, $6, 0, 0); }
    ; 

whileCommand: 
    KW_WHILE expression command                                                 { $$ = branchUp(AST_WHILE, $2, $3, 0, 0, 0); }
    ;

gotoCommand: 
    KW_GOTO label                                                               { $$ = branchUp(AST_GOTO, $2, 0, 0, 0, 0); }
    ;

expression: 
    TK_IDENTIFIER                                                               { $$ = symbolize($1); }
    | TK_IDENTIFIER '[' expression ']'                                          { $$ = branchUp(AST_VEC, symbolize($1), $3, 0, 0, 0); }
    | LIT_INTEGER                                                               { $$ = symbolize($1); }
    | LIT_CHAR                                                                  { $$ = symbolize($1); }

    | expression '+' expression                                                 { $$ = branchUp(AST_SUM, $1, $3, 0, 0, 0); }
    | expression '-' expression                                                 { $$ = branchUp(AST_SUB, $1, $3, 0, 0, 0); }
    | expression '*' expression                                                 { $$ = branchUp(AST_MUL, $1, $3, 0, 0, 0); }
    | expression '/' expression                                                 { $$ = branchUp(AST_DIV, $1, $3, 0, 0, 0); }
    | expression '<' expression                                                 { $$ = branchUp(AST_LES, $1, $3, 0, 0, 0); }
    | expression '>' expression                                                 { $$ = branchUp(AST_GRE, $1, $3, 0, 0, 0); }
    | expression OPERATOR_LE expression                                         { $$ = branchUp(AST_LEQ, $1, $3, 0, 0, 0); }
    | expression OPERATOR_GE expression                                         { $$ = branchUp(AST_GEQ, $1, $3, 0, 0, 0); }
    | expression OPERATOR_EQ expression                                         { $$ = branchUp(AST_EQU, $1, $3, 0, 0, 0); }
    | expression OPERATOR_DIF expression                                        { $$ = branchUp(AST_DIF, $1, $3, 0, 0, 0); }

    | '(' expression ')'                                                        { $$ = branchUp(AST_PAR, $2, 0, 0, 0, 0); }

    | TK_IDENTIFIER '(' listOfExpressions ')'                                   { $$ = branchUp(AST_FUNCTION_START, symbolize($1), $3, 0, 0, 0); }

    | KW_READ                                                                   { $$ = branchUp(AST_READ, 0, 0, 0, 0, 0); }

    ;

listOfExpressions:
    expression nextExpressions                                                  { $$ = branchUp(AST_LEXP_FIRST, $1, $2, 0, 0, 0);}
    |                                                                           { $$ = 0; }
    ;
nextExpressions:
    ',' expression nextExpressions                                              { $$ = branchUp(AST_LEXP_NEXT, $2, $3, 0, 0, 0);}
    |                                                                           { $$ = 0; }
    ;
    
%%

#include <stdio.h>
#include <stdlib.h>

int yyerror() {
    printf("\033[1;31m");
    fprintf(stdout, "\nER: Syntax error at line %d", getLineNumber());
    fprintf(stdout, "\nCompilation exit. CODE 3.\n");
    printf("\033[0m");
    exit(3);
}