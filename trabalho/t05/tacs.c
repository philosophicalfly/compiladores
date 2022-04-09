#include "tacs.h"

TAC *tacCreate(TAC_NAME type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2)
{
  TAC *newTac = NULL;
  newTac = (TAC *)calloc(1, sizeof(TAC));

  newTac->type = type;
  newTac->res = res;
  newTac->op1 = op1;
  newTac->op2 = op2;

  newTac->prev = NULL;
  newTac->next = NULL;

  return newTac;
}

void tacPrint(TAC *tac)
{

  FILE *file = stderr;

  if (!tac || tac->type == TAC_SYMBOL)
    return;

  fprintf(file, "TAC(");
  switch (tac->type)
  {
  case TAC_SYMBOL:
    fprintf(file, "                   ");
    break;
  case TAC_SUM:
    fprintf(file, "TAC_SUM            ");
    break;
  case TAC_SUB:
    fprintf(file, "TAC_SUB            ");
    break;
  case TAC_MUL:
    fprintf(file, "TAC_MUL            ");
    break;
  case TAC_DIV:
    fprintf(file, "TAC_DIV            ");
    break;
  case TAC_LES:
    fprintf(file, "TAC_LES            ");
    break;
  case TAC_GRE:
    fprintf(file, "TAC_GRE            ");
    break;
  case TAC_LEQ:
    fprintf(file, "TAC_LEQ            ");
    break;
  case TAC_GEQ:
    fprintf(file, "TAC_GEQ            ");
    break;
  case TAC_EQU:
    fprintf(file, "TAC_EQU            ");
    break;
  case TAC_DIF:
    fprintf(file, "TAC_DIF            ");
    break;
  case TAC_PAR:
    fprintf(file, "TAC_PAR            ");
    break;
  case TAC_VEC:
    fprintf(file, "TAC_VEC            ");
    break;
  case TAC_PRNT_START:
    fprintf(file, "TAC_PRNT_START     ");
    break;
  case TAC_PRNT_FIRST:
    fprintf(file, "TAC_PRNT_FIRST     ");
    break;
  case TAC_PRNT_NEXT:
    fprintf(file, "TAC_PRNT_NEXT      ");
    break;
  case TAC_PRNT_EXP:
    fprintf(file, "TAC_PRNT_EXP       ");
    break;
  case TAC_PRNT:
    fprintf(file, "TAC_PRNT           ");
    break;
  case TAC_RTRN:
    fprintf(file, "TAC_RTRN           ");
    break;
  case TAC_GOTO:
    fprintf(file, "TAC_GOTO           ");
    break;
  case TAC_IF:
    fprintf(file, "TAC_IF             ");
    break;
  case TAC_JUMP_FALSE:
    fprintf(file, "TAC_JUMP_FALSE     ");
    break;
  case TAC_JUMP:
    fprintf(file, "TAC_JUMP           ");
    break;
  case TAC_LABEL:
    fprintf(file, "TAC_LABEL          ");
    break;
  case TAC_ELSE:
    fprintf(file, "TAC_ELSE           ");
    break;
  case TAC_WHILE:
    fprintf(file, "TAC_WHILE          ");
    break;
  case TAC_ATTR:
    fprintf(file, "TAC_ATTR           ");
    break;
  case TAC_ATTR_VEC:
    fprintf(file, "TAC_ATTR_VEC       ");
    break;
  case TAC_LBEL:
    fprintf(file, "TAC_LBEL           ");
    break;
  case TAC_LCMD:
    fprintf(file, "TAC_LCMD           ");
    break;
  case TAC_LCMD_CURL:
    fprintf(file, "TAC_LCMD_CURL      ");
    break;
  case TAC_FUNCTION_START:
    fprintf(file, "TAC_FUNCTION_START ");
    break;
  case TAC_FUN_CALL:
    fprintf(file, "TAC_FUN_CALL       ");
    break;
  case TAC_FUN_START:
    fprintf(file, "TAC_FUN_START      ");
    break;
  case TAC_FUN_END:
    fprintf(file, "TAC_FUN_END        ");
    break;
  case TAC_LEXP_FIRST:
    fprintf(file, "TAC_LEXP_FIRST     ");
    break;
  case TAC_LEXP_NEXT:
    fprintf(file, "TAC_LEXP_NEXT      ");
    break;
  case TAC_PARAM_CALL:
    fprintf(file, "TAC_PARAM_CALL     ");
    break;
  case TAC_READ:
    fprintf(file, "TAC_READ           ");
    break;
  case TAC_FUNC_I:
    fprintf(file, "TAC_FUNC_I         ");
    break;
  case TAC_FUNC_C:
    fprintf(file, "TAC_FUNC_C         ");
    break;
  case TAC_FUNC_F:
    fprintf(file, "TAC_FUNC_F         ");
    break;
  case TAC_PARA_START:
    fprintf(file, "TAC_PARA_START     ");
    break;
  case TAC_PARA_NEXT:
    fprintf(file, "TAC_PARA_NEXT      ");
    break;
  case TAC_PARA_I:
    fprintf(file, "TAC_PARA_I         ");
    break;
  case TAC_PARA_C:
    fprintf(file, "TAC_PARA_C         ");
    break;
  case TAC_PARA_F:
    fprintf(file, "TAC_PARA_F         ");
    break;
  case TAC_LDEC:
    fprintf(file, "TAC_LDEC           ");
    break;
  case TAC_VAR_I:
    fprintf(file, "TAC_VAR_I          ");
    break;
  case TAC_VAR_C:
    fprintf(file, "TAC_VAR_C          ");
    break;
  case TAC_VAR_F:
    fprintf(file, "TAC_VAR_F          ");
    break;
  case TAC_MOVE:
    fprintf(file, "TAC_MOVE           ");
    break;
  case TAC_VECT_I:
    fprintf(file, "TAC_VECT_I         ");
    break;
  case TAC_VECT_C:
    fprintf(file, "TAC_VECT_C         ");
    break;
  case TAC_VECT_F:
    fprintf(file, "TAC_VECT_F         ");
    break;
  case TAC_LITS_STRT:
    fprintf(file, "TAC_LITS_STRT      ");
    break;
  case TAC_LITS_NEXT:
    fprintf(file, "TAC_LITS_NEXT      ");
    break;
  default:
    break;
  }
  fprintf(stderr, ", %s", tac->res ? tac->res->text : "_ ");
  fprintf(stderr, ", %s", tac->op1 ? tac->op1->text : "_ ");
  fprintf(stderr, ", %s", tac->op2 ? tac->op2->text : "_ ");
  fprintf(stderr, ");\n");
}

void tacPrintBackwards(TAC *tac)
{

  if (!tac)
    return;
  tacPrintBackwards(tac->prev);
  tacPrint(tac);
}

TAC *tacJoin(TAC *l1, TAC *l2)
{
  if (!l1)
    return l2;
  if (!l2)
    return l1;
  TAC *point = l2;
  for (point = l2; point->prev; point = point->prev)
    ;
  point->prev = l1;
  return l2;
}

TAC *generateBinaryOperation(int operation, TAC *c0, TAC *c1)
{
  return tacJoin(
      tacJoin(c0, c1),
      tacCreate(operation, makeTemp(), c0->res, c1->res));
}

TAC *generateIf(TAC *c0, TAC *c1)
{
  TAC *jumpTac = 0;
  TAC *labelTac = 0;
  HASH_NODE *new_label = 0;
  new_label = makeLabel();

  jumpTac = tacCreate(TAC_JUMP_FALSE, new_label, c0->res, 0);
  jumpTac->prev = c0;

  labelTac = tacCreate(TAC_LABEL, new_label, 0, 0);
  labelTac->prev = c1;

  return tacJoin(jumpTac, labelTac);
}

TAC *generateElse(TAC *codeOperation, TAC *codeTrue, TAC *codeFalse)
{
  TAC *jumpFalseTac = 0;
  TAC *jumpTac = 0;
  TAC *elseLabelTac = 0;
  TAC *endLabelTac = 0;
  HASH_NODE *labelIfTrue = 0;
  HASH_NODE *labelEnd = 0;
  labelIfTrue = makeLabel();
  labelEnd = makeLabel();

  jumpFalseTac = tacCreate(TAC_JUMP_FALSE, labelIfTrue, codeOperation->res, 0);
  jumpTac = tacCreate(TAC_JUMP, labelEnd, 0, 0);
  elseLabelTac = tacCreate(TAC_LABEL, labelIfTrue, 0, 0);
  endLabelTac = tacCreate(TAC_LABEL, labelEnd, 0, 0);

  return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(
                                                     codeOperation, jumpFalseTac),
                                                 codeTrue),
                                         jumpTac),
                                 elseLabelTac),
                         codeFalse),
                 endLabelTac);
}

TAC *generateWhile(TAC *codeOperation, TAC *codeTrue)
{
  TAC *jumpFalseTac = 0;
  TAC *jumpTac = 0;

  TAC *startLabelTac = 0;
  TAC *elseLabelTac = 0;
  TAC *endLabelTac = 0;

  HASH_NODE *labelStart = 0;
  labelStart = makeLabel();
  HASH_NODE *labelIfTrue = 0;
  labelIfTrue = makeLabel();
  HASH_NODE *labelEnd = 0;
  labelEnd = makeLabel();

  startLabelTac = tacCreate(TAC_LABEL, labelStart, 0, 0);
  jumpFalseTac = tacCreate(TAC_JUMP_FALSE, labelEnd, codeOperation->res, 0);
  jumpTac = tacCreate(TAC_JUMP, labelStart, 0, 0);

  return tacJoin(tacJoin(tacJoin(tacJoin(
                                     startLabelTac, codeOperation),
                                 jumpFalseTac),
                         codeTrue),
                 jumpTac);
}

TAC *generateFunction(HASH_NODE *symbol, TAC *code0, TAC *code1, TAC *code2, TAC *code3)
{
  TAC *startFuncTac = 0;
  TAC *endFuncTac = 0;

  startFuncTac = tacCreate(TAC_FUN_START, symbol, 0, 0);
  endFuncTac = tacCreate(TAC_FUN_END, symbol, 0, 0);

  return tacJoin(tacJoin(code0, tacJoin(code1, tacJoin(startFuncTac, tacJoin(code2, code3)))), endFuncTac);
}

TAC *generateCode(AST *node)
{
  TAC *code[MAX_SONS];
  TAC *result = 0;

  if (!node)
    return 0;

  int i;
  for (i = 0; i < MAX_SONS; i++)
  {
    code[i] = generateCode(node->son[i]);
  }

  switch (node->type)
  {
  case AST_SYMBOL:
    result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
    break;
  case AST_SUM:
    result = generateBinaryOperation(TAC_SUM, code[0], code[1]);
    break;
  case AST_SUB:
    result = generateBinaryOperation(TAC_SUB, code[0], code[1]);
    break;
  case AST_MUL:
    result = generateBinaryOperation(TAC_MUL, code[0], code[1]);
    break;
  case AST_DIV:
    result = generateBinaryOperation(TAC_DIV, code[0], code[1]);
    break;
  case AST_LES:
    result = generateBinaryOperation(TAC_LES, code[0], code[1]);
    break;
  case AST_GRE:
    result = generateBinaryOperation(TAC_GRE, code[0], code[1]);
    break;
  case AST_LEQ:
    result = generateBinaryOperation(TAC_LEQ, code[0], code[1]);
    break;
  case AST_GEQ:
    result = generateBinaryOperation(TAC_GEQ, code[0], code[1]);
    break;
  case AST_EQU:
    result = generateBinaryOperation(TAC_EQU, code[0], code[1]);
    break;
  case AST_DIF:
    result = generateBinaryOperation(TAC_DIF, code[0], code[1]);
    break;
  // case AST_PAR:                                                                           break;
  // case AST_VEC:                                                                           break;
  // case AST_PRNT_START:                                                                    break;
  case AST_PRNT_FIRST:
  case AST_PRNT_NEXT:
    result = tacJoin(tacCreate(TAC_PRNT, code[0]->res, 0, 0), code[1]);
    break;
  // case AST_PRNT_EXP:                                                                      break;
  case AST_RTRN:
    result = tacJoin(code[0], tacCreate(TAC_RTRN, code[0]->res, 0, 0));
    break;
  case AST_GOTO:
    result = tacJoin(code[0], tacCreate(TAC_GOTO, node->son[0]->symbol, 0, 0));
    break;
  case AST_IF:
    result = generateIf(code[0], code[1]);
    break;
  case AST_ELSE:
    result = generateElse(code[0], code[1], code[2]);
    break;
  case AST_WHILE:
    result = generateWhile(code[0], code[1]);
    break;
  case AST_ATTR:
    result = tacJoin(code[1], tacCreate(TAC_ATTR, node->son[0]->symbol, code[1]->res, 0));
    break;
  case AST_ATTR_VEC:
    result = tacJoin(code[1], tacCreate(TAC_ATTR_VEC, node->son[0]->symbol, code[1]->res, code[2]->res));
    break;
  case AST_LBEL:
    result = tacJoin(tacCreate(TAC_LABEL, code[0]->res, 0, 0), code[1]);
    break;
  // case AST_LCMD:                                                                          break;
  // case AST_LCMD_CURL:                                                                     break;
  case AST_FUNCTION_START:
    result = tacJoin(code[1], tacCreate(TAC_FUN_CALL, makeTemp(), code[0]->res, 0));
    break;
  case AST_LEXP_FIRST:
  case AST_LEXP_NEXT:
    result = tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_PARAM_CALL, code[0]->res, 0, 0));
    break;
  case AST_READ:
    result = tacCreate(TAC_READ, makeTemp(), 0, 0);
    break; // ask
  case AST_FUNC_I:
  case AST_FUNC_C:
  case AST_FUNC_F:
    result = generateFunction(node->son[1]->symbol, code[0], code[1], code[2], code[3]);
    break;
  // case AST_PARA_START:                                                                    break;
  // case AST_PARA_NEXT:                                                                     break;
  // case AST_PARA_I:                                                                        break;
  // case AST_PARA_C:                                                                        break;
  // case AST_PARA_F:                                                                        break;
  // case AST_LDEC:                                                                          break;
  // case AST_VAR_I:                                                                         break;
  // case AST_VAR_C:                                                                         break;
  // case AST_VAR_F:                                                                         break;
  // case AST_VECT_I:                                                                        break;
  // case AST_VECT_C:                                                                        break;
  // case AST_VECT_F:                                                                        break;
  // case AST_LITS_STRT:                                                                     break;
  // case AST_LITS_NEXT:
  default:
    result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], tacJoin(code[3], code[4]))));
    break;
  }
  return result;
}
