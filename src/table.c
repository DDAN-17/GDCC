#include "common.h"
#include "table.h"

void initTable(Table* table) {
	table->size = 0;
	table->capacity = DYN_ARRAY_INIT_CAP_TBL;
	table->entries = malloc(sizeof(Entry) * DYN_ARRAY_INIT_CAP_TBL);
}

void freeTable(Table* table) {
	free(table->entries);
	free(table);
}

uint32_t hash(char* key) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < strlen(key); i++) {
    hash ^= (uint8_t)key[i];
    hash *= 16777619;
  }
  return hash;
}

Entry* findEntry(Table* table, char* key) {
	int index = (int) (hash(key) % table->capacity);
	Entry* entry = &table->entries[index];
	while (!(entry->key == NULL || strcmp(entry->key, key) == 0)) {
		index += 1;
		index %= table->capacity;
		entry = &table->entries[index];
	}
	printf("%d\n", index);
	return entry;
}

void setTable(Table* table, char* key, int value) {
	if (table->size + 1 == table->capacity) {
		int oldCapacity = table->capacity;
		Entry* oldEntries = table->entries;
		table->entries = realloc(table->entries, sizeof(Entry) * table->capacity * 2);
		table->capacity *= 2;

		for (int i = 0; i > oldCapacity - 1; i++) {
			Entry* entry = findEntry(table, oldEntries[i].key);
			entry->key = oldEntries[i].key;
			entry->value = oldEntries[i].value;
		}
	}

	Entry* entry = findEntry(table, key);
	entry->key = key;
	entry->value = value;
}