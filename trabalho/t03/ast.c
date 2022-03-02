// AST - Abstract Syntax Tree

#include <stdio.h>
#include "ast.h"

AST *astCreate(int type, HASH_NODE *symbol, AST *s0, AST *s1, AST *s2, AST *s3, AST *s4)
{

    AST *newnode = (AST *)calloc(1, sizeof(AST));

    newnode->type = type;
    newnode->symbol = symbol;
    newnode->son[0] = s0;
    newnode->son[1] = s1;
    newnode->son[2] = s2;
    newnode->son[3] = s3;
    newnode->son[4] = s4;

    return newnode;
}

void astPrint(AST *node, int level)
{
    if (!node)
    {
        return;
    }

    for (int i = 0; i < level; i++)
    {
        fprintf(stderr, "\033[0;34m");
        fprintf(stderr, "│  ");
        fprintf(stderr, "\033[0m");
    }

    if (node->symbol)
    {
        fprintf(stderr, "%s ", node->symbol->text);
    }

    switch (node->type)
    {
    case AST_SYMBOL:        fprintf(stderr, "AST_SYMBOL");      break;
    // Expressions
    case AST_SUM:           fprintf(stderr, "AST_SUM");         break;
    case AST_SUB:           fprintf(stderr, "AST_SUB");         break;
    case AST_MUL:           fprintf(stderr, "AST_MUL");         break;
    case AST_DIV:           fprintf(stderr, "AST_DIV");         break;
    case AST_LES:           fprintf(stderr, "AST_LES");         break;
    case AST_GRE:           fprintf(stderr, "AST_GRE");         break;
    case AST_LEQ:           fprintf(stderr, "AST_LEQ");         break;
    case AST_GEQ:           fprintf(stderr, "AST_GEQ");         break;
    case AST_EQU:           fprintf(stderr, "AST_EQU");         break;
    case AST_DIF:           fprintf(stderr, "AST_DIF");         break;
    case AST_PAR:           fprintf(stderr, "AST_PAR");         break;
    case AST_VEC:           fprintf(stderr, "AST_VEC");         break;

    case AST_PRNT_START:    fprintf(stderr, "AST_PRNT_START");  break;
    case AST_PRNT_FIRST:    fprintf(stderr, "AST_PRNT_FIRST");  break;
    case AST_PRNT_NEXT:     fprintf(stderr, "AST_PRNT_NEXT");   break;
    case AST_PRNT_EXP:      fprintf(stderr, "AST_PRNT_EXP");    break;
    case AST_RTRN:          fprintf(stderr, "AST_RTRN");        break;
    case AST_GOTO:          fprintf(stderr, "AST_GOTO");        break;
    case AST_IF:            fprintf(stderr, "AST_IF");          break;
    case AST_ELSE:          fprintf(stderr, "AST_ELSE");        break;
    case AST_WHILE:         fprintf(stderr, "AST_WHILE");       break;

    // Extra
    case AST_ATTR:          fprintf(stderr, "AST_ATTR");        break;
    case AST_ATTR_VEC:      fprintf(stderr, "AST_ATTR_VEC");    break;
    case AST_LBEL:          fprintf(stderr, "AST_LBEL");        break;
    case AST_LCMD:          fprintf(stderr, "AST_LCMD");        break;
    case AST_LCMD_CURL:     fprintf(stderr, "AST_LCMD_CURL");   break;

    // Function Call
    case AST_LEXP_START:    fprintf(stderr, "AST_LEXP_START");  break;
    case AST_LEXP_FIRST:    fprintf(stderr, "AST_LEXP_FIRST");  break;
    case AST_LEXP_NEXT:     fprintf(stderr, "AST_LEXP_NEXT");   break;
    case AST_READ:          fprintf(stderr, "AST_READ");        break;

    // Function Decl
    case AST_FUNC:          fprintf(stderr, "AST_FUNC");        break;
    case AST_PARA_START:    fprintf(stderr, "AST_PARA_START");  break;
    case AST_PARA_NEXT:     fprintf(stderr, "AST_PARA_NEXT");   break;
    case AST_PARA:          fprintf(stderr, "AST_PARA");        break;

    // Var Declaration
    case AST_LDEC:          fprintf(stderr, "AST_LDEC");        break;
    case AST_VARI:          fprintf(stderr, "AST_VARI");        break;
    case AST_VARF:          fprintf(stderr, "AST_VARF");        break;

    // Vector Decl
    case AST_VECT:          fprintf(stderr, "AST_VECT");        break;
    case AST_LITS_STRT:     fprintf(stderr, "AST_LITS_STRT");   break;
    case AST_LITS_NEXT:     fprintf(stderr, "AST_LITS_NEXT");   break;

    default:                fprintf(stderr, "AST_DEFAULT");     break;
    }

    fprintf(stderr, "\n");

    for (int i = 0; i < MAX_SONS; i++)
        astPrint(node->son[i], level + 1);
}

// END OF FILE