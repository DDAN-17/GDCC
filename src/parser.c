#include "common.h"
#include "parser.h"
#include "scanner.h"
#include "trigger.h"
#include "table.h"

typedef struct {
	Token current;
	Token previous;
	TriggerArray array;
	Table* symbolTable;
	BoolArray openItems;
	char* functionName;
	int freeGroup;
} Parser;

Parser parser;

TriggerArray startParser() {
	initTriggerArray(&parser.array);
	parser.symbolTable = (Table*) malloc(sizeof(Table));
	initTable(parser.symbolTable);
	return parser.array;
}

static void advance() {
	parser.previous = parser.current;
	parser.current = nextToken();
}

static bool match(TokenType type) {
	if (parser.current.type == type) {
		advance();
		return true;
	}
	return false;
}

static int reserveGroup(char* symbol) {
	setTable(parser.symbolTable, symbol, parser.freeGroup);
	return parser.freeGroup++;
}

static long reserveItem() {
	for (int i = 0;;i++) {
		if (&parser.openItems.bools[i] == NULL || parser.openItems.bools[i] == false) {
			writeBoolArray(parser.openItems, i, true);
			return (long) i;
		}
	}
}

long or() {
	long expr = and();

	while (match(TOKEN_OR)) {
      Token operator = parser.previous;
      long right = and();
      expr = reserveItem();
    }
}

long expression() {
	return or();
}