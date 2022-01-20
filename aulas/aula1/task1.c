// C Program to demonstrate fscanf
#include <stdio.h>

// Driver Code
int main()
{
    char lineBuffer[100];
    int numberCounter = 0;

    FILE *filePtr = fopen("in1.txt", "r");
    if (filePtr == NULL)
    {
        printf("no such file.");
        return 0;
    }

    while (fscanf(filePtr, "%s", lineBuffer) == 1)
    {
        printf("%s\n", lineBuffer);
        lineBuffer[0] = '\0';
        numberCounter++;
    }

    printf("Number of numbers: %d\n", numberCounter);

}