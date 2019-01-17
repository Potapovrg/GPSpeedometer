
#include "GPS_Parser.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))


int32_t Diff (int32_t deg1, int32_t deg2);
uint32_t CosFix (int32_t angle);

uint32_t DistanceBetween (Position *p1, Position *p2);