#include "common.h"
#include "scanner.h"
#include "localization.h"
#include "parser.h"

char* tokenVal(Token t);
void error(char* message);
void warning(char* message);

char* prgName;

char* readFile(const char* path);

int main(int argc, char** argv) {
    prgName = argv[0];
    if (argc == 1) {
        error(NO_INPUT_FILE_MSG);
    }
    char* file = readFile(argv[argc - 1]);
    initScanner(file);

    #if BUILD_MODE == DEBUG && defined(TOKENS_OUT)
    while (scannerHasNextToken()) {
        Token t = nextToken();
        printf("%s\t %d \n", tokenVal(t), t.type);
    }
    exit(0);
    #endif

    startParser();
}

char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
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