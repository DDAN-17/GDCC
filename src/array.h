#ifndef array_h
#define array_h

typedef struct {
	int size;
	int capacity;
	int* ints;
} IntArray;

void initIntArray(IntArray array);
void writeIntArray(IntArray array, int value);
void freeIntArray(IntArray array);

#endif