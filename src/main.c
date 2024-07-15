#include "common.h"
#include "scanner.h"

char* tokenVal(Token t);

int main(int argc, char** argv) {
    if (argc == 1) {
        fprintf(stderr, "%s: %serror:%s No input files\n", argv[0], BHRED, reset);
        exit(1);
    }
    printf("%s\n", tokenVal(nextToken()));
}

char* tokenVal(Token t) {
    char* string = malloc(strlen(t.start));
    strcpy(string, t.start);
    string[t.length] = '\0';
    return string;
}