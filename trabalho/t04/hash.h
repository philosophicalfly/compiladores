// Referência:
// Código majoritariamente retirado das video aulas
//      da disciplina INF01147 da UFRGS,
//      do Professor Marcelo Johann

#ifndef HASH_HEADER

#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SONS        5
#define HASH_SIZE       4999

// Converted types
#define SYMBOL_KW_CHAR          1001
#define SYMBOL_KW_INT           1002
#define SYMBOL_KW_FLOAT         1003
#define SYMBOL_KW_READ          1004
#define SYMBOL_TK_IDENTIFIER    1005

#define SYMBOL_LIT_INTEGER      1006
#define SYMBOL_LIT_CHAR         1007
#define SYMBOL_LIT_STRING       1008

// Created types
#define SYMBOL_VARIABLE         1010
#define SYMBOL_VECTOR           1011
#define SYMBOL_PARAMETER        1012
#define SYMBOL_FUNCTION         1013
#define SYMBOL_LABEL            1014

// Data Types
#define DATATYPE_INT            1000
#define DATATYPE_CHAR           1001
#define DATATYPE_FLOAT          1002
#define DATATYPE_BOOL           1003

// Structure Types
#define SRUCTURE_VARIABLE       1000
#define SRUCTURE_VECTOR         1001
#define SRUCTURE_FUNCTION       1002

typedef struct astnode AST;

typedef struct hashNode
{
    int type;
    int dataType;
    int structureType;
    char *text;
    struct hashNode *next;
    AST *paramList;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);

int hashCheckUndeclared(void);

int getFunctionDatatype(int AST_TYPE);
int getVariableDatatype(int AST_TYPE);
int getVectorDatatype(int AST_TYPE);
int getParameterDatatype(int AST_TYPE);
int getSymbolDatatype(int AST_TYPE);

#endif
