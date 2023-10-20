#include "util.h"

extern const unsigned int res[2];

unsigned int coordToIdx(Coord st, Coord bound) {
	return (st._y * bound._x) + st._x;
}

Coord idxToCoord(unsigned int i, Coord bound) {
	Coord st = {
		i % bound._x,
		i % bound._y
	};

	return st;
}

int inRng(int val, int floor, int roof) {
	return val >= floor && val <= roof;
}

float norm(unsigned int val, axis_t axis) {
	return val / (float) res[axis];
}
