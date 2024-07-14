#include "common.h"
#include "scanner.h"

typedef struct {
	const char* current;
	const char* previous;
	int line;
} Scanner ;

Scanner scanner;

void initScanner(char* source) {
	scanner.start = source;
	scanner.current = source;
	scanner.line = 1;
}