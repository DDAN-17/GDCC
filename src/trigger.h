#ifndef trigger_h
#define trigger_h

#include "common.h"

typedef struct {
    TriggerType type,
    IntArray groups,
    boolean touchTriggerOrMulti, // Works as both touch trigger option and multi activate option.
    boolean spawnTrigger,
    union {
        Alpha
    } as
} Trigger ;

typedef enum {
    ALPHA
} TriggerType ;

typedef struct {
    int targetGroup,
    float opacity
} Alpha ;


#endif /* trigger_h */
