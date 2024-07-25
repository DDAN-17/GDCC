#include "common.h"
#include "array.h"

void initIntArray(IntArray* array) {
	array->size = 0;
	array->capacity = DYN_ARRAY_INIT_CAP_INT;
	array->ints = (int*) malloc(DYN_ARRAY_INIT_CAP_INT * sizeof(int));
}

void writeIntArray(IntArray* array, int value) {
	if (array->size + 1 == array->capacity) {
		int oldCap = array->capacity;
		array->ints = realloc(array->ints, oldCap * sizeof(int) * 2);
		array->capacity = oldCap * 2;
	}

	array->ints[array->size++] = value;
}
void freeIntArray(IntArray* array) {
	free(array->ints);
	free(array);
}

void initStringArray(StringArray* array) {
	array->size = 0;
	array->capacity = DYN_ARRAY_INIT_CAP_STR;
	array->strings = (char**) malloc(DYN_ARRAY_INIT_CAP_STR * sizeof(char*));
}

int writeStringArray(StringArray* array, char* value) {
	if (array->size + 1 == array->capacity) {
		int oldCap = array->capacity;
		array->strings = realloc(array->strings, oldCap * sizeof(int) * 2);
		array->capacity = oldCap * 2;
	}

	array->strings[array->size++] = value;
	return array->size - 1;
}
void freeStringArray(StringArray* array) {
	free(array->strings);
	free(array);
}

void initBoolArray(BoolArray* array) {
	array->capacity = DYN_ARRAY_INIT_CAP_BOL;
	array->bools = (bool*) malloc(DYN_ARRAY_INIT_CAP_BOL * sizeof(bool));
}

void writeBoolArray(BoolArray* array, int index, bool value) {
	while (index >= array->capacity) {
		int oldCap = array->capacity;
		array->bools = realloc(array->bools, oldCap * sizeof(bool) * 2);
		array->capacity = oldCap * 2;
	}

	array->bools[index] = value;
}
void freeBoolArray(BoolArray* array) {
	free(array->bools);
	free(array);
}