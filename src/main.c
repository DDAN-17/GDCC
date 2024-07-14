#include "common.h"
#include "scanner.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        fprintf(stderr, "%s: %serror:%s No input files\n", argv[0], BHRED, reset);
        exit(1);
    }
    initScanner("Scanner Test");
}
