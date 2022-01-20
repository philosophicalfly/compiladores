// C Program to demonstrate fscanf
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int stringHasNumber(const char *s)
{
    int hasNumber = 0;
    while (*s)
    {
        if (isdigit(*s++))
            hasNumber = 1;
    }

    return hasNumber;
}

int main()
{
    FILE *filePtr = fopen("in2.txt", "r");
    if (filePtr == NULL)
    {
        printf("no such file.");
        return 0;
    }

    // Reading lines separated by ;
    char lineBuffer[100];
    char lastchar;
    int numbersByVirtualLine[100] = {0};
    int numberCounter = 0;
    int lineCounter = 0;
    int virtualLineCounter = 0;
    int physicalLineCounter = 0;

    int scannedCharsLen = 0;
    int scannedCharsPos = 0;
    while (fscanf(filePtr, "%s", lineBuffer) == 1)
    {

        scannedCharsLen = strlen(lineBuffer);
        if (stringHasNumber(lineBuffer))
        {
            numbersByVirtualLine[virtualLineCounter]++;
        }

        for (scannedCharsPos = 0; scannedCharsPos < scannedCharsLen; scannedCharsPos++)
        {
            if (lineBuffer[scannedCharsPos] == ';')
            {
                virtualLineCounter++;
            }
        }
        numberCounter++;
    }

    // Reading physical lines
    rewind(filePtr);

    while (fgets(lineBuffer, 100, filePtr))
    {
        printf("%s", lineBuffer);
        physicalLineCounter++;
    }

    // Displaying
    int displayCounter = 0;
    for (displayCounter = 0; displayCounter < virtualLineCounter; displayCounter++)
    {
        printf("%d ", numbersByVirtualLine[displayCounter]);
    }

    printf("\nNumber of numbers: %d\n", numberCounter);
    printf("Number of virtual lines: %d\n", virtualLineCounter);
    printf("Number of physical lines: %d\n", physicalLineCounter);
}