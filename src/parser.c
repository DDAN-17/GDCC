#include "common.h"
#include "parser.h"
#include "scanner.h"
#include "trigger.h"
#include "table.h"
#include "localization.h"

typedef struct {
	Token current;
	Token previous;
	TriggerArray* array;
	Table* symbolTable;
	BoolArray* scratchItems;
	BoolArray* openItems;
	char* functionName;
	int expressionNum;
} Parser;

Parser parser;

long expression();
static void advance();

TriggerArray* startParser() {
	parser.openItems = (BoolArray*) malloc(sizeof(BoolArray));
	initBoolArray(parser.openItems);
	parser.array = (TriggerArray*) malloc(sizeof(TriggerArray));
	initTriggerArray(parser.array);
	parser.symbolTable = (Table*) malloc(sizeof(StringArray));
	initTable(parser.symbolTable);
	advance();
	expression();
	return parser.array;
}

static void advance() {
	if (parser.current.type == TOKEN_EOF) {
		return;
	}
	parser.previous = parser.current;
	parser.current = nextToken();
}

static bool match(TokenType type) {
	if (parser.current.type == TOKEN_EOF) {
		return false;
	}
	if (parser.current.type == type) {
		advance();
		return true;
	}
	return false;
}

static int reserveGroup(char* symbol) {
	Entry* entry = findEntry(parser.symbolTable, symbol);
	return entry->value;
}

static long reserveItem() {
	for (int i = 0;;i++) {
		if (parser.openItems->bools[i] == false || &parser.openItems->bools[i] == NULL) {
			writeBoolArray(parser.openItems, i, true);
			writeBoolArray(parser.scratchItems, i, true);
			return i;
		}
	}
}

long primary() {
	puts("Test: Segfault?");
	if (match(TOKEN_IDENTIFIER)) {
		if (strcmp(tokenVal(&parser.previous), (char*) "true") == 0) {
			return 1;
		} else if (strcmp(tokenVal(&parser.previous), (char*) "false") == 0) {
			return 0;
		}
	}
	return -1;
}

long buildSub(long left, long right, int group, long out) {
	Trigger* itemEdit = (Trigger*) initTrigger(TRIGGER_ITEM_EDIT);
	itemEdit->as.itemEdit.itemID1 = left;
    itemEdit->as.itemEdit.itemID2 = right;
    itemEdit->as.itemEdit.targetItemID = out;
    writeIntArray(itemEdit->groups, group);
    itemEdit->as.itemEdit.operator2 = operatorMinus;
    return out;
}

long buildDiv(long left, long right, int group, long out) {
	Trigger* itemEdit = (Trigger*) initTrigger(TRIGGER_ITEM_EDIT);
	itemEdit->as.itemEdit.itemID1 = left;
    itemEdit->as.itemEdit.itemID2 = right;
    itemEdit->as.itemEdit.targetItemID = out;
    writeIntArray(itemEdit->groups, group);
    itemEdit->as.itemEdit.operator2 = operatorDivide;
    return out;
}

long buildNeg(long right, int group, long out) {
	Trigger* itemEdit = (Trigger*) initTrigger(TRIGGER_ITEM_EDIT);
    itemEdit->as.itemEdit.itemID2 = right;
    itemEdit->as.itemEdit.targetItemID = out;
    writeIntArray(itemEdit->groups, group);
    itemEdit->as.itemEdit.sign1 = signNeg;
    return out;
}

long buildAdd(long left, long right, int group, long out) {
	Trigger* itemEdit = (Trigger*) initTrigger(TRIGGER_ITEM_EDIT);
	itemEdit->as.itemEdit.itemID1 = left;
    itemEdit->as.itemEdit.itemID2 = right;
    itemEdit->as.itemEdit.targetItemID = out;
    writeIntArray(itemEdit->groups, group);
    itemEdit->as.itemEdit.operator2 = operatorPlus;
    return out;
}

long buildNot(long right, int group, long out) {
	buildNeg(right, group, out);
	buildAdd(0, out, group, out);
	return out;
}

long buildEqual(long left, long right, int group, long out) {
	buildSub(left, right, group, out);
	buildDiv(out, out, group, out);
	buildNot(out, group, out);
	return out;
}

long buildNotEqual(long left, long right, int group, long out) {
	buildSub(left, right, group, out);
	buildDiv(out, out, group, out);
	return out;
}

long equality() {
	long expr = primary();
	printf("%d\n", (int) expr);
	//long expr = 0;

	//bool equal = false;

	while (match(TOKEN_EQUAL_EQUAL) || match(TOKEN_BANG_EQUAL)) {
		//equal = false;
		//if (parser.previous.type == TOKEN_EQUAL_EQUAL) {
		//	equal = true;
		//}
      	//long right = primary();
      
      	//char* str;
      	//asprintf(&str, "%sEqualityProc%d", parser.functionName, parser.expressionNum);
      	//if (equal) {
      		//expr = buildEqual(expr, right, reserveGroup(str), reserveItem());
      	//} else {
      		//expr = buildNotEqual(expr, right, reserveGroup(str), reserveItem());
      	//}
    }
    return 0;
    //return expr;
}

long buildAnd(long left, long right, int group, long out) {
	Trigger* itemEdit = (Trigger*) initTrigger(TRIGGER_ITEM_EDIT);
    itemEdit->as.itemEdit.itemID1 = left;
    itemEdit->as.itemEdit.itemID2 = right;
    itemEdit->as.itemEdit.mod = 2;
    itemEdit->as.itemEdit.targetItemID = out;
    writeIntArray(itemEdit->groups, group);
    itemEdit->as.itemEdit.operator3 = operatorDivide;
    itemEdit->as.itemEdit.float1 = floatFlr;
    return out;
}

long and() {
	long expr = equality();

	while (match(TOKEN_AND)) {
	  long right = equality();

      char* str;
      asprintf(&str, "%sAndProc%d", parser.functionName, parser.expressionNum);
      expr = buildAnd(expr, right, reserveGroup(str), reserveItem());
    }
    return expr;
}

long buildOr(long left, long right, int group, long out) {
	Trigger* itemEdit = (Trigger*) initTrigger(TRIGGER_ITEM_EDIT);
    itemEdit->as.itemEdit.itemID1 = left;
    itemEdit->as.itemEdit.itemID2 = right;
    itemEdit->as.itemEdit.mod = 2;
    itemEdit->as.itemEdit.targetItemID = out;
    writeIntArray(itemEdit->groups, group);
    itemEdit->as.itemEdit.operator3 = operatorDivide;
    itemEdit->as.itemEdit.float1 = floatCei;
    return out;
}

long or() {
	long expr = and();

	while (match(TOKEN_OR)) {
      long right = and();
      char* str;
      asprintf(&str, "%sOrProc%d", parser.functionName, parser.expressionNum);
      expr = buildOr(expr, right, reserveGroup(str), reserveItem());
    }
    return expr;
}

long expression() {
	//return 0;
	return or();
}