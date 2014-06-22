#include <stdio.h>

#define MAX_READ_LENGTH 10000

FILE *inputFile;
char charsRead[MAX_READ_LENGTH];

int getChars() {
    extern char charsRead[MAX_READ_LENGTH];
    extern FILE *inputFile;
    if (fgets(charsRead, MAX_READ_LENGTH, inputFile) == NULL) {
        fclose(inputFile);
        return 0;
    }
    return 1;
}

int main() {
    extern FILE *inputFile;
    inputFile = fopen("replaceComments.c", "r");

    extern char charsRead[MAX_READ_LENGTH];
    int currentChar;

    if (inputFile == NULL) {
        fprintf(stderr, "Can't open replaceComments.c!\n");
        return 1;
    }

    int currentCharIndex = 0;

    // Used for when we're looking for the start of a comment.
    int encounteredSlash = 0;

    // Used for when we're looking for the end of a comment.
    int encounteredStar = 0;

    // Indicates whether we are in a comment.
    int inComment = 0;

    // Indicates whether we leave a comment at the end of the line (double
    // slash comment).
    int leaveCommentAtEndOfLine = 0;

    while (getChars() && charsRead != NULL) {
        while ((currentChar = charsRead[currentCharIndex]) != '\0') {
            // If we encountered a slash before, check if we are in
            // a comment.
            if (encounteredSlash) {
                if (currentChar == '*' || currentChar == '/') {
                    inComment = 1;
                    leaveCommentAtEndOfLine = currentChar == '/';
                } else {
                    // If we are not in a comment, print the slash from before.
                    printf("/");
                }
                encounteredSlash = 0;
            }

            currentCharIndex++;

            if (inComment) {
                if (leaveCommentAtEndOfLine && currentChar == '\n') {
                    inComment = leaveCommentAtEndOfLine = 0;
                } else if (encounteredStar) {
                    // If we encountered a star before (and are in a comment), check if
                    // we are about to leave a comment.
                    inComment = currentChar == '/';
                    encounteredStar = 0;
                } else {
                    encounteredStar = currentChar == '*';
                }
                // Don't print anything if we're in a comment.
                continue;
            }

            if (!(encounteredSlash = currentChar == '/')) {
                // Print if a slash wasn't encountered.
                printf("%c", currentChar);
            }
        }
        currentCharIndex = 0;
    }

    return 0;
}
