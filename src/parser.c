#include "common.h"
#include "parser.h"
#include "scanner.h"
#include "trigger.h"

typedef struct {
	Token current;
	Token previous;
} Parser;

Parser parser;

TriggerArray startParser() {
	TriggerArray array;
	initTriggerArray(array);
	return array;
}