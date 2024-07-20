#ifndef table_h
#define table_h

#define DYN_ARRAY_INIT_CAP_TBL 16

typedef struct {
	char* key;
	int value;
} Entry;

typedef struct {
	int size;
	int capacity;
	Entry* entries;
} Table;

void initTable(Table* table);
Entry* findEntry(Table* table, char* key);
void setTable(Table* table, char* key, int value);
void freeTable(Table* table);
uint32_t hash(char* key);

#endif