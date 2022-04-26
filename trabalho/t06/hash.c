// Referência:
// Código majoritariamente retirado das video aulas
//      da disciplina INF01147 da UFRGS,
//      do Professor Marcelo Johann

#include "hash.h"

HASH_NODE *Table[HASH_SIZE];
int dataTypesArr[3] = {DATATYPE_INT, DATATYPE_CHAR, DATATYPE_FLOAT};
char dataTypesPrint[3][6] = {"INT  \0", "CHAR \0", "FLOAT\0"};
char dataStrucPrint[3][6] = {"VAR  \0", "VEC  \0", "FUN  \0"};
void printVectorValuesASM(FILE *file, AST *node);

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
            // fprintf(stderr, "\n   NODE: %s %s\n", text, node->text);
            return node;
        }
    return 0;
}

// Insere na tabela se o nó não existe ainda
HASH_NODE *hashInsert(char *text, int type)
{
    HASH_NODE *newnode;
    char initVal[2] = {'0', '\0'};
    int address = hashAddress(text);
    if ((newnode = hashFind(text)) != 0)
    {
        return newnode;
    }
    newnode = (HASH_NODE *)calloc(1, sizeof(HASH_NODE));
    newnode->type = type;
    newnode->text = (char *)calloc(strlen(text) + 1, sizeof(char));
    strcpy(newnode->text, text);
    newnode->initVal = (char *)calloc(strlen(initVal) + 1, sizeof(char));
    strcpy(newnode->initVal, initVal);
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
            // printf("Addr: %d\t Type: %d\tTken: %s\n", i, node->type, node->text);
            char dataTypeString[6] = "     \0";
            if (node->dataType)
                strcpy(dataTypeString, dataTypesPrint[(node->dataType) - 1000]);
            char dataStructString[6] = "     \0";
            if (node->structureType)
                strcpy(dataStructString, dataStrucPrint[(node->structureType) - 1000]);
            printf("Addr: %d\t Type: %d\tDaTy:\t%s\tStru:\t%s\tTken: %s\n ", i, node->type, dataTypeString, dataStructString, node->text);
        }
    }
}

void hashPrintASM(FILE *file)
{
    int i;
    HASH_NODE *node;

    for (i = 0; i < HASH_SIZE; ++i)
    {
        for (node = Table[i]; node; node = node->next)
        {
            if (node->structureType == SRUCTURE_VECTOR)
            {
                fprintf(file,
                        "_%s:\n",
                        node->text);
                printVectorValuesASM(file, node->initValues);
            }
            else
            {
                if (node->type == SYMBOL_LIT_STRING)
                {
                    // remove quotes
                    char newString[100];
                    char *noQuotesString;
                    strcpy(newString, node->text);
                    noQuotesString = newString;
                    noQuotesString++;
                    noQuotesString[strlen(noQuotesString) - 1] = 0;
                    for (int i = 0; i < strlen(noQuotesString); ++i)
                    {
                        // if it is not alphabet, remove from the name
                        if (!((noQuotesString[i] >= 'a' && noQuotesString[i] <= 'z') || (noQuotesString[i] >= 'A' && noQuotesString[i] <= 'Z')))
                            noQuotesString[i] = '_';
                    }

                    // add new line to the end of the format
                    char newString2[100];
                    char strngEnd[4] = {'\\', 'n', '\"', '\0'};
                    char *printFormat;
                    strcpy(newString2, node->text);
                    printFormat = newString2;
                    printFormat[strlen(printFormat) - 1] = 0;
                    strcat(printFormat, strngEnd);

                    fprintf(file,
                            "._%s:\n"
                            "   .string    %s\n",
                            noQuotesString, printFormat);
                }
                if (node->type == SYMBOL_VARIABLE)
                {
                    fprintf(file,
                            "_%s:\n"
                            "   .long    %s\n",
                            node->text, node->initVal);
                }
                if (node->type == SYMBOL_PARAMETER)
                {
                    fprintf(file,
                            "_%s:\n"
                            "   .long    0\n",
                            node->text);
                }
                if (node->type == SYMBOL_LIT_INTEGER)
                {
                    fprintf(file,
                            "_%s:\n"
                            "   .long    %s\n",
                            node->text, node->text);
                }
                if (node->type == SYMBOL_LIT_CHAR)
                {
                    fprintf(file,
                            "_%d:\n"
                            "   .byte    %d\n",
                            node->text[1], node->text[1]);
                }
            }
        }
    }
}

// Imprime a tabela
int hashCheckUndeclared(void)
{
    int i;
    int undeclared = 0;
    HASH_NODE *node;
    for (i = 0; i < HASH_SIZE; ++i)
    {
        for (node = Table[i]; node; node = node->next)
        {
            if (node->type == SYMBOL_TK_IDENTIFIER)
            {
                ++undeclared;
                printf("Semantic ERROR: Undeclared token %s\n", node->text);
            }
        }
    }
    return undeclared;
}

HASH_NODE *makeTemp()
{
    static int serial = 0;
    char buffer[256] = ".";

    sprintf(buffer, "OMEGATemp%d", serial++);
    return hashInsert(buffer, SYMBOL_VARIABLE);
}

HASH_NODE *makeLabel()
{
    static int serial = 0;
    char buffer[256] = ".";

    sprintf(buffer, "LAMBDALabel%d", serial++);
    return hashInsert(buffer, SYMBOL_LABEL_TAC);
}

int getFunctionDatatype(int AST_TYPE)
{
    return dataTypesArr[AST_TYPE - 50];
}

int getVariableDatatype(int AST_TYPE)
{
    return dataTypesArr[AST_TYPE - 60];
}

int getVectorDatatype(int AST_TYPE)
{
    return dataTypesArr[AST_TYPE - 70];
}

int getParameterDatatype(int AST_TYPE)
{
    return dataTypesArr[AST_TYPE - 80];
}

int getSymbolDatatype(int AST_TYPE)
{
    if (AST_TYPE == SYMBOL_LIT_INTEGER)
        return DATATYPE_INT;
    if (AST_TYPE == SYMBOL_LIT_CHAR)
        return DATATYPE_CHAR;
    // AST_TYPE == SYMBOL_LIT_FLOAT
    return DATATYPE_FLOAT;
}
