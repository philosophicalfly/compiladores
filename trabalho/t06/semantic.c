#include "semantic.h"

int SemanticErrors = 0;

int dataTypeInfer(int type1, int type2)
{
  if (type1 && type2)
  { // Equals
    if (type1 == type2)
      return type1;
    // Int
    if (type1 == DATATYPE_INT && type2 == DATATYPE_CHAR)
      return DATATYPE_INT;
    if (type1 == DATATYPE_INT && type2 == DATATYPE_FLOAT)
      return DATATYPE_FLOAT;
    // Char
    if (type1 == DATATYPE_CHAR && type2 == DATATYPE_INT)
      return DATATYPE_INT;
    if (type1 == DATATYPE_CHAR && type2 == DATATYPE_FLOAT)
      return DATATYPE_FLOAT;
    // Float
    if (type1 == DATATYPE_FLOAT && type2 == DATATYPE_INT)
      return DATATYPE_FLOAT;
    if (type1 == DATATYPE_FLOAT && type2 == DATATYPE_CHAR)
      return DATATYPE_FLOAT;
    // Bool only with bool
    if (type1 == DATATYPE_BOOL && type2 != DATATYPE_BOOL)
      return 0;
    if (type1 != DATATYPE_BOOL && type2 == DATATYPE_BOOL)
      return 0;
  }
  return 0;
}

int assignTypeCheck(int variable, int data)
{
  if (!variable || !data)
    return 0;
  else
  {
    // FLOAT gets all except by bool
    if (variable == DATATYPE_FLOAT &&
        data == DATATYPE_BOOL)
      return 0;
    // INT gets CHAR
    if (variable == DATATYPE_INT &&
        (data == DATATYPE_BOOL ||
         data == DATATYPE_FLOAT))
      return 0;
    // CHAR gets INT
    if (variable == DATATYPE_CHAR &&
        (data == DATATYPE_BOOL ||
         data == DATATYPE_FLOAT))
      return 0;
    // BOOL gets BOOL only
    if (variable == DATATYPE_BOOL &&
        data != DATATYPE_BOOL)
      return 0;
  }
  return 1;
}

int getSymbolType(AST *node)
{
  HASH_NODE *hashNode;
  // fprintf(stderr, "SYMBOL TYPE %d\n\n", node->symbol->type);
  if (node)
    if (node->symbol)
      if (node->symbol->type)
        switch (node->symbol->type)
        {
        case SYMBOL_LIT_INTEGER:
        case SYMBOL_KW_INT:
          return DATATYPE_INT;

        case SYMBOL_LIT_CHAR:
        case SYMBOL_KW_CHAR:
          return DATATYPE_CHAR;

        case SYMBOL_LIT_STRING:
          return DATATYPE_CHAR;

        case SYMBOL_KW_FLOAT:
          return DATATYPE_FLOAT;

        case SYMBOL_VARIABLE:
        case SYMBOL_VECTOR:
        case SYMBOL_PARAMETER:
        case SYMBOL_FUNCTION:
          hashNode = hashFind(node->symbol->text);
          return hashNode->dataType;
        }
  return 0;
}

int getFunctionType(AST *node)
{
  char *functionName = node->son[0]->symbol->text;
  HASH_NODE *declaration = hashFind(functionName);
  return declaration->dataType;
}

int getDataType(AST *node)
{
  int dataType = 0;
  int leftDataType = 0;
  int rightDataType = 0;

  if (node == 0)
    return 0;

  switch (node->type)
  {
  case AST_VAR_I:
  case AST_VAR_C:
  case AST_VAR_F:
    dataType = getVariableDatatype(node->type);
    break;
  case AST_VEC:
    dataType = getSymbolType(node->son[0]);
    node->son[0]->symbol->dataType = dataType; // Do i need it?
    break;
  case AST_SYMBOL:
    dataType = getSymbolType(node);
    node->symbol->dataType = dataType; // Do i need it?
    break;
  case AST_FUNCTION_START:
    dataType = getFunctionType(node);
    break;
  case AST_FUNC_I:
  case AST_FUNC_C:
  case AST_FUNC_F:
    dataType = getFunctionType(node);
    break;
  case AST_SUM:
  case AST_SUB:
  case AST_MUL:
    leftDataType = getDataType(node->son[0]);
    rightDataType = getDataType(node->son[1]);
    dataType = dataTypeInfer(leftDataType, rightDataType);
    break;
  case AST_DIV:
    leftDataType = getDataType(node->son[0]);
    rightDataType = getDataType(node->son[1]);
    dataType = dataTypeInfer(leftDataType, rightDataType);
    // dataType = DATATYPE_FLOAT;
    break;
  case AST_LES:
  case AST_GRE:
  case AST_LEQ:
  case AST_GEQ:
  case AST_EQU:
  case AST_DIF:
    // leftDataType = getDataType(node->son[0]);
    // rightDataType = getDataType(node->son[1]);
    // dataType = dataTypeInfer(leftDataType, rightDataType);
    dataType = DATATYPE_BOOL;
    break;
  case AST_READ:
    dataType = DATATYPE_INT;
    break;
  case AST_PAR:
  case AST_RTRN:
    dataType = getDataType(node->son[0]);
    break;
  default:
    break;
  }
  return dataType;
}

int checkSemanticErrors()
{
  return SemanticErrors;
}

int typesMatch(int master, int new)
{
  return dataTypeInfer(master, new);
  // return master == new;
}

int parametersMatch(AST *declaration, AST *invocation)
{
  AST *nextDeclarationParam = NULL;
  AST *nextInvocationParam = NULL;
  int typesAreMatched = 0;
  if (declaration && invocation)
  {

    // astPrint(declaration, 0);
    // fprintf(stderr, "INVO\n");
    // astPrint(invocation, 0);
    int declarationDataType = declaration->son[0]->son[1]->symbol->dataType;
    int invocationDataType = getDataType(invocation->son[0]);
    // fprintf(stderr, "declarationDataType %d\n", declarationDataType);
    // fprintf(stderr, "invocationDataType %d\n", invocationDataType);
    if (declaration->son ? declaration->son[1] : NULL)
      nextDeclarationParam = declaration->son[1];
    if (invocation->son[1])
      nextInvocationParam = invocation->son[1];
    typesAreMatched = typesMatch(declarationDataType, invocationDataType);
    if (!nextDeclarationParam && !nextInvocationParam && typesAreMatched)
      return 1;
    if (nextDeclarationParam && nextInvocationParam && typesAreMatched)
      return parametersMatch(nextDeclarationParam, nextInvocationParam);
  }
  return 0;
}

int validateParameters(AST *invocation)
{

  int noOneHasParams = 0;
  int sameParameterCountAndType = 0;
  char *functionName = invocation->son[0]->symbol->text;
  HASH_NODE *declaration = hashFind(functionName);
  AST *declarationParamList = NULL;
  AST *invocationParamList = NULL;
  if (declaration->paramList)
    declarationParamList = declaration->paramList;
  if (invocation->son[1])
    invocationParamList = invocation->son[1];
  noOneHasParams = !declarationParamList && !invocationParamList;
  if (noOneHasParams)
    return 1;
  sameParameterCountAndType = parametersMatch(declarationParamList, invocationParamList);
  return sameParameterCountAndType;
}

void validateFunctionReturn(AST *node, int functionDataType, int *returnPointer)
{
  int returnDataType = 0;

  if (!node)
    return;

  if (node->type == AST_RTRN)
  {
    returnDataType = getDataType(node);
    // fprintf(stderr, "\n\n\nfunctionDataType %d\n", functionDataType);
    // fprintf(stderr, "\n\n\nreturnDataType   %d\n\n", returnDataType);
    if (returnDataType != functionDataType)
      *returnPointer = 0;
  }

  for (int i = 0; i < MAX_SONS; i++)
    validateFunctionReturn(node->son[i], functionDataType, returnPointer);
}

int isArithmeticIdentifier(AST *node)
{
  int isIdentifier = 0;
  int isArithmetic = 0;
  isIdentifier = node->type == AST_SYMBOL;
  if (node->symbol)
  {
    isArithmetic = node->symbol->dataType == DATATYPE_INT ||
                   node->symbol->dataType == DATATYPE_FLOAT;
  }

  return isIdentifier && isArithmetic;
}

int isArithmeticFunction(AST *node)
{
  int isFunctionCall = 0;
  int isArithmetic = 0;
  int paramsAreValid = 0;
  AST *firstSon = node->son[0];
  isFunctionCall = node->type == AST_FUNCTION_START || node->type == AST_FUNCTION_START;
  if (firstSon)
  {
    isArithmetic = (firstSon->symbol ? firstSon->symbol->dataType == DATATYPE_INT : 0) ||
                   (firstSon->symbol ? firstSon->symbol->dataType == DATATYPE_FLOAT : 0);
  }
  paramsAreValid = validateParameters(node);

  return isFunctionCall && isArithmetic && paramsAreValid;
}

int isNumber(AST *node)
{
  return node->symbol ? node->symbol->type == SYMBOL_LIT_INTEGER : 0;
}

int isArthmeticOperation(AST *node)
{
  return node->type == AST_SUM ||
         node->type == AST_SUB ||
         node->type == AST_DIV ||
         node->type == AST_MUL;
}

void check_and_set_declaration(AST *node)
{

  if (!node)
  {
    return;
  }

  AST *firstSon = NULL;
  AST *secondSon = NULL;
  AST *thirdSon = NULL;
  if (node->son[0])
    firstSon = node->son[0];
  if (node->son[1])
    secondSon = node->son[1];
  if (node->son[2])
    thirdSon = node->son[2];

  int datatype = 0;
  switch (node->type)
  {

  case AST_FUNC_I:
  case AST_FUNC_C:
  case AST_FUNC_F:
    datatype = getFunctionDatatype(node->type);
    if (secondSon->symbol)
    {
      if (secondSon->symbol->type != SYMBOL_TK_IDENTIFIER)
      {
        fprintf(stderr, "Semantic ERROR: Function %s already declared\n", secondSon->symbol->text);
        ++SemanticErrors;
      }
      secondSon->symbol->type = SYMBOL_FUNCTION;
      secondSon->symbol->dataType = datatype;
      secondSon->symbol->structureType = SRUCTURE_FUNCTION;
      secondSon->symbol->paramList = thirdSon;
    }
    break;

  case AST_VAR_I:
  case AST_VAR_C:
  case AST_VAR_F:
    datatype = getVariableDatatype(node->type);
    if (secondSon->symbol)
    {
      if (secondSon->symbol->type != SYMBOL_TK_IDENTIFIER)
      {
        fprintf(stderr, "Semantic ERROR: Variable %s already declared\n", secondSon->symbol->text);
        ++SemanticErrors;
      }
      secondSon->symbol->type = SYMBOL_VARIABLE;
      secondSon->symbol->dataType = datatype;
      secondSon->symbol->structureType = SRUCTURE_VARIABLE;
      secondSon->symbol->initVal = thirdSon->symbol->text;
    }
    break;

  case AST_VECT_I:
  case AST_VECT_C:
  case AST_VECT_F:
    datatype = getVectorDatatype(node->type);
    if (secondSon->symbol)
    {
      if (secondSon->symbol->type != SYMBOL_TK_IDENTIFIER)
      {
        fprintf(stderr, "Semantic ERROR: Variable %s already declared\n", secondSon->symbol->text);
        ++SemanticErrors;
      }
      secondSon->symbol->type = SYMBOL_VECTOR;
      secondSon->symbol->dataType = datatype;
      secondSon->symbol->structureType = SRUCTURE_VECTOR;
      secondSon->symbol->initValues = node->son[3]->son[0];
    }
    break;

  case AST_PARA_I:
  case AST_PARA_C:
  case AST_PARA_F:
    datatype = getParameterDatatype(node->type);
    if (secondSon->symbol)
    {
      if (secondSon->symbol->type != SYMBOL_TK_IDENTIFIER)
      {
        fprintf(stderr, "Semantic ERROR: Variable %s already declared\n", secondSon->symbol->text);
        ++SemanticErrors;
      }
      secondSon->symbol->type = SYMBOL_PARAMETER;
      secondSon->symbol->dataType = datatype;
      secondSon->symbol->structureType = SRUCTURE_VARIABLE;
    }
    break;

  case AST_LBEL:
    if (firstSon->symbol)
    {
      if (firstSon->symbol->type != SYMBOL_TK_IDENTIFIER)
      {
        fprintf(stderr, "Semantic ERROR: Label %s already declared\n", firstSon->symbol->text);
        ++SemanticErrors;
      }
      firstSon->symbol->type = SYMBOL_LABEL;
    }
    break;
  default:
    break;
  }

  for (int i = 0; i < MAX_SONS; i++)
    check_and_set_declaration(node->son[i]);
}

void check_undeclared()
{
  SemanticErrors += hashCheckUndeclared();
}

int getVectorAttributeCount(AST *node)
{
  if (!node)
    return 0;
  return 1 + getVectorAttributeCount(node->son[1]);
}

int getVectorSize(AST *node)
{
  int vectorDecSize = 0;
  int operandType = 0;
  if (node)
    if (node->symbol)
      if (node->symbol->text)
      {
        operandType = getDataType(node);
        if (operandType == DATATYPE_INT)
        {
          vectorDecSize = atoi(node->symbol->text);
        }
        if (operandType == DATATYPE_CHAR)
        {
          // Holy cow né gurizes
          vectorDecSize = (int)(*(*node).symbol).text[1];
        }
      }
  return vectorDecSize;
}

void checkIfStructureIsValid(AST *node, int type)
{
  // Compares structire type if it exists
  char *structure = node ? node->symbol ? node->symbol->text : "\0" : "\0";
  int structureType = node ? node->symbol ? node->symbol->structureType : 0 : 0;
  int structureIsValid = structureType == type;
  if (!structureIsValid)
  {
    fprintf(stderr, "Semantic ERROR: Data structure %d declared as structure type %d in token %s.\n", type, structureType, structure);
    ++SemanticErrors;
  }
}

void check_operands(AST *node)
{
  if (!node)
  {
    return;
  }

  int leftType = 0;
  int leftIsValid = 0;

  int rightType = 0;
  int rightIsValid = 0;

  int operandType = 0;
  int operandIsValid = 0;

  int functionDataType = 0;

  int vectorDecSize = 0;
  int vectorDecAttributesCount = 0;

  int paramsAreValid = 0;
  int returnIsValid = 1;

  int attribuitionType = 0;
  int variableType = 0;

  AST *firstSon = NULL;
  AST *secondSon = NULL;
  AST *thirdSon = NULL;
  AST *fourthSon = NULL;
  if (node->son[0])
    firstSon = node->son[0];
  if (node->son[1])
    secondSon = node->son[1];
  if (node->son[2])
    thirdSon = node->son[2];
  if (node->son[3])
    fourthSon = node->son[3];

  switch (node->type)
  {
  case AST_SUM:
  case AST_SUB:
  case AST_DIV:
  case AST_MUL:
  case AST_LES:
  case AST_GRE:
  case AST_LEQ:
  case AST_GEQ:
    leftType = getDataType(firstSon);
    rightType = getDataType(secondSon);
    leftIsValid = leftType == DATATYPE_CHAR || leftType == DATATYPE_INT || leftType == DATATYPE_FLOAT;
    rightIsValid = rightType == DATATYPE_CHAR || rightType == DATATYPE_INT || rightType == DATATYPE_FLOAT;
    if (!leftIsValid)
    {
      fprintf(stderr, "Semantic ERROR: Operation with invalid left operands\n");
      ++SemanticErrors;
    }
    if (!rightIsValid)
    {
      fprintf(stderr, "Semantic ERROR: Operation with invalid right operands\n");
      ++SemanticErrors;
    }
    break;

  case AST_EQU:
  case AST_DIF:
    leftType = getDataType(firstSon);
    rightType = getDataType(secondSon);
    leftIsValid = leftType == DATATYPE_CHAR || leftType == DATATYPE_INT || leftType == DATATYPE_FLOAT || leftType == DATATYPE_BOOL;
    rightIsValid = rightType == DATATYPE_CHAR || rightType == DATATYPE_INT || rightType == DATATYPE_FLOAT || rightType == DATATYPE_BOOL;
    if (!leftIsValid)
    {
      fprintf(stderr, "Semantic ERROR: Operation with invalid left operands\n");
      ++SemanticErrors;
    }
    if (!rightIsValid)
    {
      fprintf(stderr, "Semantic ERROR: Operation with invalid right operands\n");
      ++SemanticErrors;
    }
    break;

  case AST_FUNC_I:
  case AST_FUNC_C:
  case AST_FUNC_F:
    // Compares structure type if it exists
    checkIfStructureIsValid(secondSon, SRUCTURE_FUNCTION);
    functionDataType = getFunctionDatatype(node->type);
    validateFunctionReturn(node, functionDataType, &returnIsValid);
    if (!returnIsValid)
    {
      fprintf(stderr, "Semantic ERROR: Function return type is different from definition\n");
      ++SemanticErrors;
    }
    break;

  case AST_VECT_I:
  case AST_VECT_C:
  case AST_VECT_F:
    // Compares structure type if it exists
    checkIfStructureIsValid(secondSon, SRUCTURE_VECTOR);
    vectorDecSize = getVectorSize(thirdSon);
    if (fourthSon)
      if (fourthSon->son[0])
        vectorDecAttributesCount = getVectorAttributeCount(fourthSon->son[0]);
    if (vectorDecSize < vectorDecAttributesCount)
    {
      fprintf(stderr, "Semantic ERROR: Vector Attributes exceeds vector size\n");
      ++SemanticErrors;
    }
    break;

  case AST_FUNCTION_START:
    // Compares structure type if it exists
    checkIfStructureIsValid(firstSon, SRUCTURE_FUNCTION);
    paramsAreValid = validateParameters(node);
    functionDataType = getDataType(node);
    if (!paramsAreValid)
    {
      fprintf(stderr, "Semantic ERROR: Function parameters are not valid\n");
      ++SemanticErrors;
    }
    break;

  case AST_IF:
  case AST_ELSE:
  case AST_WHILE:
    operandType = getDataType(firstSon);
    operandIsValid = operandType == DATATYPE_BOOL;
    if (!operandIsValid)
    {
      fprintf(stderr, "Semantic ERROR: Got not boolean expression in boolean comparison\n");
      ++SemanticErrors;
    }
    break;

  case AST_PAR:
    operandType = getDataType(firstSon);
    if (!operandType)
    {
      fprintf(stderr, "Semantic ERROR: Parentheses parameters are not valid\n");
      ++SemanticErrors;
    }
    break;

  case AST_ATTR:
    // Compares structure type if it exists
    checkIfStructureIsValid(firstSon, SRUCTURE_VARIABLE);
    attribuitionType = getDataType(secondSon);
    variableType = getDataType(firstSon);
    // fprintf(stderr, "variableDataType  %d\n", variableType);
    // fprintf(stderr, "attribuiType      %d\n", secondSon->type);
    // fprintf(stderr, "attribuiDataType  %d\n", attribuitionType);
    operandIsValid = typesMatch(variableType, attribuitionType);
    if (!operandIsValid)
    {
      fprintf(stderr, "Semantic ERROR: Attribuition type is not valid\n");
      ++SemanticErrors;
    }
    break;

  case AST_ATTR_VEC:
  case AST_VEC:
    // Compares structure type if it exists
    checkIfStructureIsValid(firstSon, SRUCTURE_VECTOR);
    attribuitionType = getDataType(secondSon);
    operandIsValid = attribuitionType == DATATYPE_CHAR || attribuitionType == DATATYPE_INT;
    if (!operandIsValid)
    {
      fprintf(stderr, "Semantic ERROR: Array index type is not valid\n");
      ++SemanticErrors;
    }
    break;
  default:
    break;
  }

  for (int i = 0; i < MAX_SONS; i++)
    check_operands(node->son[i]);
}

void printNode(AST *node)
{
  fprintf(stderr, "\033[0;34m");
  fprintf(stderr, "\n----------------------NODE INIT--------------------");
  if (node->type)
    fprintf(stderr, "\nAST Type:  %d", node->type);
  if (node->symbol)
  {
    if (node->symbol->text)
      fprintf(stderr, "\nHASH Text: %s", node->symbol->text);
    if (node->symbol->type)
      fprintf(stderr, "\nHASH Type: %d", node->symbol->type);
    if (node->symbol->dataType)
      fprintf(stderr, "\nHASH DaTy: %d", node->symbol->dataType);
  }
  fprintf(stderr, "\nNODE END");
  fprintf(stderr, "\n---------------------------------------------------\n");
  fprintf(stderr, "\033[0m");
}
