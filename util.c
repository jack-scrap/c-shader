#include "util.h"

extern const unsigned int res[2];

unsigned int coordToIdx(Coord st, Coord bound) {
	return (st._y * bound._x) + st._x;
}

int inRng(int val, int floor, int roof) {
	return val >= floor && val <= roof;
}

float norm(unsigned int val, axis_t axis) {
	return val / (float) res[axis];
}
