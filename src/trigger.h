#ifndef trigger_h
#define trigger_h

#include "common.h"
#include "array.h"

#define DYN_ARRAY_INIT_CAP_TRIG 8

typedef enum {
    ALPHA
} TriggerType;

typedef struct {
    int targetGroup;
    float opacity;
} Alpha;

typedef struct {
    TriggerType type;
    IntArray groups;
    bool touchTriggerOrMulti; // Works as both touch trigger option and multi activate option.
    bool spawnTrigger;
    union {
        Alpha alpha;
    } as;
} Trigger;

typedef struct {
    int capacity;
    int size;
    Trigger* triggers;
} TriggerArray;

void initTriggerArray(TriggerArray* array);
void writeTriggerArray(TriggerArray* array, Trigger value);
void freeTriggerArray(TriggerArray* array);

#endif
