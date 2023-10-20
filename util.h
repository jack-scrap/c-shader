#ifndef UTIL_H
#define UTIL_H

#include "math.h"

unsigned int coordToIdx(Coord st, Coord bound);

Coord idxToCoord(unsigned int i, Coord bound);

int inRng(int val, int floor, int roof);

float norm(unsigned int val, axis_t axis);

#endif
