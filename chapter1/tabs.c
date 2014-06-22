#include <stdio.h>

#define MAX_INPUT_LINE_LENGTH 10000
#define TAB_WIDTH 4

int currentChar;

int getValidChar() {
    extern int currentChar;
    currentChar = getchar();
    return ((currentChar != EOF) && (currentChar != '\n'));
}

void printSpaces(int numSpaces) {
    for (int currentSpace = 0; currentSpace < TAB_WIDTH; currentSpace++) {
        printf(" ");
    }
}

void detab() {
    int charIndex;
    extern int currentChar;

    char line[MAX_INPUT_LINE_LENGTH];

    for (charIndex = 0;
            charIndex < MAX_INPUT_LINE_LENGTH - 1 && getValidChar();
            charIndex++) {
        if (currentChar != '\t') {
            printf("%c", currentChar);
        } else {
            printSpaces(TAB_WIDTH);
        }
    }
    printf("\n");
}

void entab() {
    int charIndex;
    int consecutiveSpaceCount = 0;
    extern int currentChar;

    char line[MAX_INPUT_LINE_LENGTH];

    for (charIndex = 0;
            charIndex < MAX_INPUT_LINE_LENGTH - 1 && getValidChar();
            charIndex++) {
        if (currentChar != ' ') {
            if (consecutiveSpaceCount > 0) {
                printSpaces(consecutiveSpaceCount);
            }
            consecutiveSpaceCount = 0;

            printf("%c", currentChar);
        } else {
            consecutiveSpaceCount++;
            if (consecutiveSpaceCount == TAB_WIDTH) {
                printf("\t");
                consecutiveSpaceCount = 0;
            }
        }
    }
    printf("\n");
}

int main() {
    entab();
}
