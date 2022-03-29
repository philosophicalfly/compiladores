#include "hash.h"
#include "ast.h"

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER
#endif

extern int SemanticErrors;

void printNode(AST *node);
void check_and_set_declaration(AST *node);
void check_undeclared();
void check_operands(AST *node);
void check_and_set_declaration(AST *node);
