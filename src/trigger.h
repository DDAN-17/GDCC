#ifndef trigger_h
#define trigger_h

#include "common.h"
#include "array.h"

#define DYN_ARRAY_INIT_CAP_TRIG 8

#define operatorEquals 0
#define operatorPlus 1
#define operatorMinus 2
#define operatorTimes 3
#define operatorDivide 4

#define comparisonEquals 0
#define comparisonGreater 1
#define comparisonGreaterEquals 2
#define comparisonLess 3
#define comparisonLessEquals 4
#define comparisonNotEquals 5

#define signNone 0
#define signAbs 1
#define signNeg 2

#define floatNone 0
#define floatRnd 1
#define floatFlr 2
#define floatCei 3

typedef enum {
    TRIGGER_ALPHA,
    TRIGGER_ITEM_EDIT,
    TRIGGER_ITEM_COMPARE
} TriggerType;

typedef struct {
    int groupID;
    float opacity;
} Alpha;

typedef struct {
    long itemID1;
    long itemID2;
    int mod;
    long targetItemID;
    uint8_t operator1;
    uint8_t operator2;
    uint8_t operator3;
    uint8_t sign1;
    uint8_t sign2;
    uint8_t float1;
    uint8_t float2;
} ItemEdit;

typedef struct {
    long itemID1;
    long itemID2;
    int mod1;
    int mod2;
    int trueID;
    int falseID;
    uint8_t operator1;
    uint8_t operator2;
    uint8_t comparison;
} ItemCompare;

typedef struct {
    TriggerType type;
    IntArray* groups;
    bool touchTrigger;
    bool multiActivate;
    bool spawnTrigger;
    union {
        Alpha alpha;
        ItemEdit itemEdit;
        ItemCompare itemCompare;
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

void* initTrigger(TriggerType t);

#endif
