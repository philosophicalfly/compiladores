// AST — Abstract Syntax Tree

#include "hash.h"

#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS        5

#define AST_SYMBOL      1

#define AST_SUM         2
#define AST_SUB         3
#define AST_MUL         4
#define AST_DIV         5
#define AST_LES         6
#define AST_GRE         7
#define AST_LEQ         8
#define AST_GEQ         9
#define AST_EQU         10
#define AST_DIF         11
#define AST_PAR         12
#define AST_VEC         13

#define AST_PRNT_START  14
#define AST_PRNT_FIRST  15
#define AST_PRNT_NEXT   16
#define AST_PRNT_EXP    17
#define AST_RTRN        18
#define AST_GOTO        19
#define AST_IF          20
#define AST_ELSE        21
#define AST_WHILE       22

#define AST_ATTR        40
#define AST_ATTR_VEC    41

#define AST_LBEL        30
#define AST_LCMD        31
#define AST_LCMD_CURL   32
#define AST_LEXP_START  33
#define AST_LEXP_FIRST  34
#define AST_LEXP_NEXT   35
#define AST_READ        36

#define AST_FUNC        50
#define AST_PARA_START  51
#define AST_PARA_NEXT   52
#define AST_PARA        53

#define AST_LDEC        60
#define AST_VARI        61
#define AST_VARF        62

#define AST_VECT        63
#define AST_LITS_STRT   64
#define AST_LITS_NEXT   65


#define symbolize(symbol) astCreate(AST_SYMBOL, symbol, 0, 0, 0, 0, 0)
#define branchUp(type, s0, s1, s2, s3, s4) astCreate(type, 0, s0, s1, s2, s3, s4)
typedef struct astnode
{
    int type;
    struct astnode *son[MAX_SONS];
    HASH_NODE *symbol;
} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST *s0, AST *s1, AST *s2, AST *s3, AST *s4);
void astPrint(AST *node, int level);

#endif

// END OF FILE
