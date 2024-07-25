#ifndef array_h
#define array_h

#define DYN_ARRAY_INIT_CAP_INT 1
#define DYN_ARRAY_INIT_CAP_BOL 16
#define DYN_ARRAY_INIT_CAP_STR 8

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

typedef struct {
	int size;
	int capacity;
	char** strings;
} StringArray;

void initStringArray(StringArray* array);
int writeStringArray(StringArray* array, char* value);
void freeStringArray(StringArray* array);

#endif