#ifndef common_h
#define common_h

#define en_US 0

#define DEBUG 0
#define RELEASE 1

#include "config.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ansi.h"

char* concat(char *s1, char *s2);

void error(char* msg);
void warning(char* msg);

#endif
