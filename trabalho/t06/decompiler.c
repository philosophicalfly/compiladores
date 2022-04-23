#include "decompiler.h"

void decompileAST_SYMBOL(AST *node, FILE *file)
{
    fprintf(file, "%s", node->symbol->text);
}

void decompileAST_SUM(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " + ");
    decompile(node->son[1], file);
}

void decompileAST_SUB(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " - ");
    decompile(node->son[1], file);
}

void decompileAST_MUL(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " * ");
    decompile(node->son[1], file);
}

void decompileAST_DIV(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " / ");
    decompile(node->son[1], file);
}

void decompileAST_LES(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " < ");
    decompile(node->son[1], file);
}

void decompileAST_GRE(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " > ");
    decompile(node->son[1], file);
}

void decompileAST_LEQ(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " <= ");
    decompile(node->son[1], file);
}

void decompileAST_GEQ(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " >= ");
    decompile(node->son[1], file);
}

void decompileAST_EQU(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " == ");
    decompile(node->son[1], file);
}

void decompileAST_DIF(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " != ");
    decompile(node->son[1], file);
}

void decompileAST_VEC(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, "[");
    decompile(node->son[1], file);
    fprintf(file, "]");
}

void decompileAST_PRNT_START(AST *node, FILE *file)
{
    fprintf(file, "print ");
    decompile(node->son[0], file);
}

void decompileAST_PRNT_FIRST(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    decompile(node->son[1], file);
}

void decompileAST_PRNT_NEXT(AST *node, FILE *file)
{
    fprintf(file, ", ");
    decompile(node->son[0], file);
    decompile(node->son[1], file);
}

void decompileAST_PRNT_EXP(AST *node, FILE *file)
{
    fprintf(file, ", ");
    decompile(node->son[0], file);
    decompile(node->son[1], file);
}

void decompileAST_RTRN(AST *node, FILE *file)
{
    fprintf(file, "return ");
    decompile(node->son[0], file);
}

void decompileAST_GOTO(AST *node, FILE *file)
{
    fprintf(file, "goto ");
    decompile(node->son[0], file);
}

void decompileAST_PAR(AST *node, FILE *file)
{
    fprintf(file, "(");
    decompile(node->son[0], file);
    fprintf(file, ")");
}

void decompileAST_LBEL(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, ":\n");
    decompile(node->son[1], file);
}

void decompileAST_LCMD(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " ;\n");
    decompile(node->son[1], file);
}

void decompileAST_LCMD_CURL(AST *node, FILE *file)
{
    fprintf(file, " {\n");
    decompile(node->son[0], file);
    fprintf(file, " } ");
}

void decompileAST_ATTR(AST *node, FILE* file)
{
  decompile(node->son[0], file);
  fprintf(file, " = ");
  decompile(node->son[1], file);
}

void decompileAST_ATTR_VEC(AST *node, FILE* file)
{
  decompile(node->son[0], file);
  fprintf(file, " [ ");
  decompile(node->son[1], file);
  fprintf(file, " ] = ");
  decompile(node->son[2], file);
}

void decompileAST_FUNCTION_START(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    fprintf(file, " ( ");
    decompile(node->son[1], file);
    fprintf(file, " ) ");
}

void decompileAST_LEXP_FIRST(AST *node, FILE *file)
{
    decompile(node->son[0], file);
    decompile(node->son[1], file);
}

void decompileAST_LEXP_NEXT(AST *node, FILE *file)
{
    fprintf(file, " , ");
    decompile(node->son[0], file);
    decompile(node->son[1], file);
}

void decompileAST_READ(AST *node, FILE *file)
{
    fprintf(file, "read");
}

void decompileAST_WHILE(AST *node, FILE* file)
{
  fprintf(file, " while ");
  decompile(node->son[0], file);
  decompile(node->son[1], file);
}

void decompileAST_IF(AST *node, FILE* file)
{
  fprintf(file, " if ");
  decompile(node->son[0], file);
  fprintf(file, " then \n");
  decompile(node->son[1], file);
}

void decompileAST_ELSE(AST *node, FILE* file)
{
  fprintf(file, " if ");
  decompile(node->son[0], file);
  fprintf(file, " then \n");
  decompile(node->son[1], file);
  fprintf(file, "\nelse \n");
  decompile(node->son[2], file);
}

void decompileAST_FUNC(AST *node, FILE* file)
{
  decompile(node->son[0], file);
  fprintf(file, " ");
  decompile(node->son[1], file);
  fprintf(file, " ( ");
  decompile(node->son[2], file);
  fprintf(file, " ) ");
  decompile(node->son[3], file);
}

void decompileAST_PARA_START(AST *node, FILE* file)
{
  decompile(node->son[0], file);
  decompile(node->son[1], file);
}

void decompileAST_PARA_NEXT(AST *node, FILE* file)
{
  fprintf(file, " , ");
  decompile(node->son[0], file);
  decompile(node->son[1], file);
}

void decompileAST_PARA(AST *node, FILE* file)
{
  decompile(node->son[0], file);
  fprintf(file, " ");
  decompile(node->son[1], file);
}

void decompileAST_LDEC(AST *node, FILE* file)
{
  decompile(node->son[0], file);
  fprintf(file, "\n");
  decompile(node->son[1], file);
}

void decompileAST_VARI(AST *node, FILE* file)
{
  decompile(node->son[0], file);
  fprintf(file, " ");
  decompile(node->son[1], file);
  fprintf(file, " : ");
  decompile(node->son[2], file);
  fprintf(file, " ;");
}

void decompileAST_VARF(AST *node, FILE* file)
{
  decompile(node->son[0], file);
  fprintf(file, " ");
  decompile(node->son[1], file);
  fprintf(file, " : ");
  decompile(node->son[2], file);
  fprintf(file, " /");
  decompile(node->son[3], file);
  fprintf(file, " ; ");
}

void decompileAST_VECT(AST *node, FILE* file)
{
  decompile(node->son[0], file);
  fprintf(file, " ");
  decompile(node->son[1], file);
  fprintf(file, " [ ");
  decompile(node->son[2], file);
  fprintf(file, " ] ");
  decompile(node->son[3], file);
  fprintf(file, " ; ");
}

void decompileAST_LITS_STRT(AST *node, FILE* file)
{
  fprintf(file, " : ");
  decompile(node->son[0], file);
}

void decompileAST_LITS_NEXT(AST *node, FILE* file)
{
  decompile(node->son[0], file);
  fprintf(file, " ");
  decompile(node->son[1], file);
}


void decompile(AST *node, FILE *file)
{
    if (!node)
        return;

    switch (node->type)
    {
        case AST_SYMBOL:                    decompileAST_SYMBOL(node, file);                    break;

        case AST_SUM:                       decompileAST_SUM(node, file);                       break;
        case AST_SUB:                       decompileAST_SUB(node, file);                       break;
        case AST_MUL:                       decompileAST_MUL(node, file);                       break;
        case AST_DIV:                       decompileAST_DIV(node, file);                       break;
        case AST_LES:                       decompileAST_LES(node, file);                       break;
        case AST_GRE:                       decompileAST_GRE(node, file);                       break;
        case AST_LEQ:                       decompileAST_LEQ(node, file);                       break;
        case AST_GEQ:                       decompileAST_GEQ(node, file);                       break;
        case AST_EQU:                       decompileAST_EQU(node, file);                       break;
        case AST_DIF:                       decompileAST_DIF(node, file);                       break;
        case AST_PAR:                       decompileAST_PAR(node, file);                       break;
        case AST_VEC:                       decompileAST_VEC(node, file);                       break;

        case AST_PRNT_START:                decompileAST_PRNT_START(node, file);                break;
        case AST_PRNT_FIRST:                decompileAST_PRNT_FIRST(node, file);                break;
        case AST_PRNT_NEXT:                 decompileAST_PRNT_NEXT(node, file);                 break;
        case AST_PRNT_EXP:                  decompileAST_PRNT_EXP(node, file);                  break;
        case AST_RTRN:                      decompileAST_RTRN(node, file);                      break;
        case AST_GOTO:                      decompileAST_GOTO(node, file);                      break;
        case AST_IF:                        decompileAST_IF(node, file);                        break;
        case AST_ELSE:                      decompileAST_ELSE(node, file);                      break;
        case AST_WHILE:                     decompileAST_WHILE(node, file);                     break;

        case AST_ATTR:                      decompileAST_ATTR(node, file);                      break;
        case AST_ATTR_VEC:                  decompileAST_ATTR_VEC(node, file);                  break;
        case AST_LBEL:                      decompileAST_LBEL(node, file);                      break;
        case AST_LCMD:                      decompileAST_LCMD(node, file);                      break;
        case AST_LCMD_CURL:                 decompileAST_LCMD_CURL(node, file);                 break;

        case AST_FUNCTION_START:            decompileAST_FUNCTION_START(node, file);            break;
        case AST_LEXP_FIRST:                decompileAST_LEXP_FIRST(node, file);                break;
        case AST_LEXP_NEXT:                 decompileAST_LEXP_NEXT(node, file);                 break;
        case AST_READ:                      decompileAST_READ(node, file);                      break;

        case AST_FUNC_I:                    decompileAST_FUNC(node, file);                      break;
        case AST_FUNC_C:                    decompileAST_FUNC(node, file);                      break;
        case AST_FUNC_F:                    decompileAST_FUNC(node, file);                      break;
        case AST_PARA_START:                decompileAST_PARA_START(node, file);                break;
        case AST_PARA_NEXT:                 decompileAST_PARA_NEXT(node, file);                 break;
        case AST_PARA_I:                    decompileAST_PARA(node, file);                      break;
        case AST_PARA_C:                    decompileAST_PARA(node, file);                      break;
        case AST_PARA_F:                    decompileAST_PARA(node, file);                      break;

        case AST_LDEC:                      decompileAST_LDEC(node, file);                      break;
        case AST_VAR_I:                     decompileAST_VARI(node, file);                      break;
        case AST_VAR_C:                     decompileAST_VARI(node, file);                      break;
        case AST_VAR_F:                     decompileAST_VARF(node, file);                      break;

        case AST_VECT_I:                    decompileAST_VECT(node, file);                      break;
        case AST_VECT_C:                    decompileAST_VECT(node, file);                      break;
        case AST_VECT_F:                    decompileAST_VECT(node, file);                      break;
        case AST_LITS_STRT:                 decompileAST_LITS_STRT(node, file);                 break;
        case AST_LITS_NEXT:                 decompileAST_LITS_NEXT(node, file);                 break;

        default:                                                                                break;
    }
}
