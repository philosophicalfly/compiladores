// Referência:
// Código majoritariamente retirado das video aulas
//      da disciplina INF01147 da UFRGS,
//      do Professor Marcelo Johann

#include "hash.h"

HASH_NODE *Table[HASH_SIZE];

// Inicia a tabela hash
void hashInit(void)
{
    int i;
    for (i = 0; i < HASH_SIZE; ++i)
    {
        Table[i] = 0;
    }
}

// Multiplica os caracteres e
// tira o resto de um primo para gerar um
// endereço quase aleatorio
int hashAddress(char *text)
{
    int address = 1;
    int i;
    for (i = 0; i < strlen(text); ++i)
    {
        address = (address * text[i]) % HASH_SIZE + 1;
    }
    return address - 1;
}

// Busca na lista encadeada do endereço
// pelo elemento enviado
HASH_NODE *hashFind(char *text)
{
    HASH_NODE *node;
    int address = hashAddress(text);
    for (node = Table[address]; node; node = node->next)
        if (strcmp(node->text, text) == 0)
        {
            fprintf(stderr, "\n   REPEATED:");
            return node;
        }
    return 0;
}

// Insere na tabela se o nó não existe ainda
HASH_NODE *hashInsert(char *text, int type)
{

    HASH_NODE *newnode;
    int address = hashAddress(text);
    if ((newnode = hashFind(text)) != 0)
    {
        return newnode;
    }
    newnode = (HASH_NODE *)calloc(1, sizeof(HASH_NODE));
    newnode->type = type;
    newnode->text = (char *)calloc(strlen(text) + 1, sizeof(char));
    strcpy(newnode->text, text);
    newnode->next = Table[address];
    Table[address] = newnode;
    return newnode;
}

// Imprime a tabela
void hashPrint(void)
{
    int i;
    HASH_NODE *node;
    for (i = 0; i < HASH_SIZE; ++i)
    {
        for (node = Table[i]; node; node = node->next)
        {
            printf("%d:\t %s\n", i, node->text);
        }
    }
}
