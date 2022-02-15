// Referência:
// Código majoritariamente retirado das video aulas 
//      da disciplina INF01147 da UFRGS,
//      do Professor Marcelo Johann 

#ifndef HASH_HEADER

#define HASH_HEADER

#include <stdio.h>

#define HASH_SIZE 4999

typedef struct hash_node
{
    int type;
    char *text;
    struct hash_node *next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);

#endif
