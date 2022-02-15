%token KW_CHAR
%token KW_INT
%token KW_FLOAT
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_GOTO
%token KW_READ
%token KW_PRINT
%token KW_RETURN
%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_CHAR
%token LIT_STRING
%token TOKEN_ERROR

%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF '<' '>' 
%left '+' '-'
%left '*' '/'

%{
int yylex();
int yyerror();
%}

%%

programa: 
    listOfDeclarations
    ;

listOfDeclarations: 
    declaration listOfDeclarations
    | 
    ;

declaration: 
    varDeclaration
    | vectorDeclaration
    | functionDeclaration
    ;

singleLiteral:  
    LIT_INTEGER
    | LIT_CHAR
    ;

varDeclaration:
    KW_INT TK_IDENTIFIER ':' singleLiteral ';'
    | KW_CHAR TK_IDENTIFIER ':' singleLiteral ';'
    | KW_FLOAT TK_IDENTIFIER ':' LIT_INTEGER '/' LIT_INTEGER ';'
    ;

vectorDeclaration:
    KW_INT TK_IDENTIFIER '[' singleLiteral ']' vectorInitializationList
    | KW_CHAR TK_IDENTIFIER '[' singleLiteral ']' vectorInitializationList
    | KW_FLOAT TK_IDENTIFIER '[' singleLiteral ']' vectorInitializationList
    ;

vectorInitializationList:
    ':' singleLiteralSequence ';'
    | ';'
    ;

singleLiteralSequence: 
    singleLiteral singleLiteralSequence
    | singleLiteral  
    ;

functionDeclaration:
    KW_CHAR TK_IDENTIFIER '(' parameterList ')' command
    | KW_INT TK_IDENTIFIER '(' parameterList ')' command
    | KW_FLOAT TK_IDENTIFIER '(' parameterList ')' command
    ;
 
parameterList: 
    parameter nextParameter
    |
    ;
    
nextParameter:
    ',' parameter nextParameter
    | 
    ;

parameter:
    KW_CHAR     TK_IDENTIFIER
    | KW_INT    TK_IDENTIFIER
    | KW_FLOAT  TK_IDENTIFIER
    ; 

listOfCommands: 
    command ';' optionalNextCommand
    | label ':' optionalNextCommand
    ;

optionalNextCommand:
    listOfCommands 
    |
    ;

label:
    TK_IDENTIFIER
    ;
    
command: 
    '{' '}'
    | '{' listOfCommands '}'
    | attribuitionCommand 
    | printCommand
    | returnCommand
    | ifCommand
    | elseCommand
    | whileCommand
    | gotoCommand
    |
    ;

attribuitionCommand: 
    TK_IDENTIFIER '=' expression
    | TK_IDENTIFIER '[' expression ']' '=' expression
    ;

printCommand:
    KW_PRINT listToPrint
    ;

listToPrint:
    printExpression nextToPrint
    ;

nextToPrint: 
    ',' printExpression nextToPrint
    |
    ;

printExpression: 
    LIT_STRING 
    | expression

returnCommand:
    KW_RETURN expression
    ;

ifCommand:
    KW_IF expression KW_THEN command
    ;

elseCommand:
    KW_IF expression KW_THEN command KW_ELSE command
    ; 

whileCommand: 
    KW_WHILE expression command
    ;

gotoCommand: 
    KW_GOTO label
    ;

expression: 
    TK_IDENTIFIER
    | TK_IDENTIFIER '[' expression ']'
    | LIT_INTEGER
    | LIT_CHAR

    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '<' expression
    | expression '>' expression

    | expression OPERATOR_LE expression
    | expression OPERATOR_GE expression
    | expression OPERATOR_EQ expression
    | expression OPERATOR_DIF expression

    | '(' expression ')'

    | TK_IDENTIFIER '(' listOfExpressions ')'

    | KW_READ
    
    ;

listOfExpressions:
    expression nextExpressions
    ;
nextExpressions:
    ',' expression nextExpressions
    | 
    ;

%%

int yyerror() {
    printf("\033[1;31m");
    fprintf(stdout, "\nER: Syntax error at line %d", getLineNumber());
    fprintf(stdout, "\nCompilation exit. CODE 3.\n");
    printf("\033[0m");
    exit(3);
}