#include "common.h"
#include "trigger.h"

void initTriggerArray(TriggerArray array) {
	
}

void addTrigger(TriggerArray array, Trigger t) {
	if (array.capacity == array.size + 1) {
		// Grow Array
	}

	array.triggers[array.size++] = t;
}