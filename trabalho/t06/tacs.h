#ifndef TACS_HEADER
#define TACS_HEADER
#endif

#include "hash.h"
#include "ast.h"
#include <stdio.h>

typedef enum
{
    TAC_SYMBOL,
    TAC_SUM,
    TAC_SUB,
    TAC_MUL,
    TAC_DIV,
    TAC_LES,
    TAC_GRE,
    TAC_LEQ,
    TAC_GEQ,
    TAC_EQU,
    TAC_DIF,
    TAC_PAR,
    TAC_VEC,
    TAC_PRNT_START,
    TAC_PRNT_FIRST,
    TAC_PRNT_NEXT,
    TAC_PRNT_EXP,
      TAC_PRNT,
    TAC_RTRN,
    TAC_GOTO,
    TAC_IF,
      TAC_JUMP_FALSE,
      TAC_JUMP,
      TAC_LABEL,
    TAC_ELSE,
    TAC_WHILE,
    TAC_ATTR,
    TAC_ATTR_VEC,
    TAC_LBEL,
    TAC_LCMD,
    TAC_LCMD_CURL,
    TAC_FUNCTION_START,
      TAC_FUN_CALL,
    TAC_LEXP_FIRST,
    TAC_LEXP_NEXT,
      TAC_PARAM_CALL,
    TAC_READ,
    TAC_FUNC_I,
    TAC_FUNC_C,
    TAC_FUNC_F,
      TAC_FUN_START,
      TAC_FUN_END,
    TAC_PARA_START,
    TAC_PARA_NEXT,
    TAC_PARA_I,
    TAC_PARA_C,
    TAC_PARA_F,
    TAC_LDEC,
    TAC_VAR_I,
    TAC_VAR_C,
    TAC_VAR_F,
      TAC_MOVE,
    TAC_VECT_I,
    TAC_VECT_C,
    TAC_VECT_F,
    TAC_LITS_STRT,
    TAC_LITS_NEXT,
} TAC_NAME;

typedef struct tac_node
{
    int type;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    struct tac_node *prev;
    struct tac_node *next;
} TAC;

TAC *tacCreate(TAC_NAME type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
void tacPrint(TAC *tac);
void tacPrintBackwards(TAC *tac);

// Code generation
TAC *generateCode(AST *node);
TAC *tacJoin(TAC *tac1, TAC *tac2);

void decompile(AST *node, FILE *file);