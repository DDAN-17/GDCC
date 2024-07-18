#include "common.h"
#include "scanner.h"
#include "localization.h"

char* tokenVal(Token t);

int main(int argc, char** argv) {
    if (argc == 1) {
        fprintf(stderr, "%s: %serror:%s %s\n", argv[0], BHRED, reset, NO_INPUT_FILE_ERR);
        exit(1);
    }
    initScanner("Hello! This is a test.");
    printf("%s\n", tokenVal(nextToken()));
}

char* tokenVal(Token t) {
    char* string = malloc(strlen(t.start));
    strcpy(string, t.start);
    string[t.length] = '\0';
    return string;
}