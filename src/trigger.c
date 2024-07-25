#include "common.h"
#include "trigger.h"
#include "array.h"
#include "localization.h"

void error(char* msg);

void initTriggerArray(TriggerArray* array) {
	array->size = 0;
	array->capacity = DYN_ARRAY_INIT_CAP_TRIG;
	array->triggers = (Trigger*) malloc(DYN_ARRAY_INIT_CAP_TRIG * sizeof(Trigger));
}

void writeTriggerArray(TriggerArray* array, Trigger value) {
	if (array->size + 1 == array->capacity) {
		int oldCap = array->capacity;
		array->triggers = (Trigger*) realloc(array->triggers, oldCap * sizeof(Trigger) * 2);
		array->capacity = oldCap * 2;
	}

	array->triggers[array->size++] = value;
}
void freeTriggerArray(TriggerArray* array) {
	free(array->triggers);
	free(array);
}

void* initTrigger(TriggerType t) {
	Trigger* trigger = (Trigger*) malloc(sizeof(Trigger));
	trigger->groups = (IntArray*) malloc(sizeof(IntArray));
	trigger->type = t;
	trigger->spawnTrigger = true;
	trigger->touchTrigger = false;
	trigger->multiActivate = true;
	initIntArray(trigger->groups);
	switch (t) {
		case TRIGGER_ALPHA:
			trigger->as.alpha.groupID = 0;
			trigger->as.alpha.opacity = 1;
			return (void*) trigger;
		case TRIGGER_ITEM_EDIT:
			trigger->as.itemEdit.itemID1 = 0;
			trigger->as.itemEdit.itemID2 = 0;
			trigger->as.itemEdit.mod = 1;
			trigger->as.itemEdit.targetItemID = 0;
			trigger->as.itemEdit.operator1 = operatorEquals;
			trigger->as.itemEdit.operator2 = operatorPlus;
			trigger->as.itemEdit.operator3 = operatorMinus;
			trigger->as.itemEdit.sign1 = signNone;
			trigger->as.itemEdit.sign2 = signNone;
			trigger->as.itemEdit.float1 = floatNone;
			trigger->as.itemEdit.float2 = floatNone;
			return (void*) trigger;
		case TRIGGER_ITEM_COMPARE:
			trigger->as.itemCompare.itemID1 = 0;
			trigger->as.itemCompare.itemID2 = 0;
			trigger->as.itemCompare.mod1 = 1;
			trigger->as.itemCompare.mod2 = 1;
			trigger->as.itemCompare.trueID = 0;
			trigger->as.itemCompare.falseID = 0;
			trigger->as.itemCompare.operator1 = operatorEquals;
			trigger->as.itemCompare.operator2 = operatorPlus;
			trigger->as.itemCompare.comparison = operatorMinus;
			return (void*) trigger;
		default:
			error(INTERNAL_ERROR_MSG);
			return NULL;
	}
}