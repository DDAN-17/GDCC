#include "common.h"
#include "trigger.h"

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