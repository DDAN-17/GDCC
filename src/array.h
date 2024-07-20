#ifndef array_h
#define array_h

#define DYN_ARRAY_INIT_CAP_INT 1
#define DYN_ARRAY_INIT_CAP_BOL 16

typedef struct {
	int size;
	int capacity;
	int* ints;
} IntArray;

void initIntArray(IntArray* array);
void writeIntArray(IntArray* array, int value);
void freeIntArray(IntArray* array);

typedef struct {
	int capacity;
	bool* bools;
} BoolArray;

void initBoolArray(BoolArray* array);
void writeBoolArray(BoolArray* array, int index, bool value);
void freeBoolArray(BoolArray* array);

#endif