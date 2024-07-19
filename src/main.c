#include "common.h"
#include "scanner.h"
#include "localization.h"

char* tokenVal(Token t);
void error(char* message);
void warning(char* message);

char* prgName;

int main(int argc, char** argv) {
    prgName = argv[0];
    if (argc == 1) {
        error(NO_INPUT_FILE_MSG);
        
    }
    initScanner("{}()&&&");
    do {
        printf("%s\n", tokenVal(nextToken()));
    } while (scannerHasNextToken());
}

char* tokenVal(Token t) {
    char* string = malloc(strlen(t.start));
    strcpy(string, t.start);
    string[t.length] = '\0';
    return string;
}

void error(char* message) {
    fprintf(stderr, "%s: %s%s%s %s\n", prgName, BHRED, ERR_MSG, reset, message);
    exit(1);
}

void warning(char* message) {
    fprintf(stderr, "%s: %s%s%s %s\n", prgName, BHYEL, WRN_MSG, reset, message);
}