#include "util.h"

unsigned int coordToIdx(Coord st, Coord bound) {
	return (st._y * bound._x) + st._x;
}

int inRng(int val, int floor, int roof) {
	return val >= floor && val <= roof;
}
