#include "common.h"
#include "scanner.h"

typedef struct {
	const char* start;
	const char* current;
	int line;
} Scanner ;

Scanner scanner;

void initScanner(char* source) {
	scanner.start = source;
	scanner.current = source;
	scanner.line = 1;
}

char* nextToken() {
	
}