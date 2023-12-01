#include "util.h"

unsigned int coordToIdx(Coord* st, Coord* bound) {
	return (st->y * bound->x) + st->x;
}

Coord localize(Coord* st, Coord* bound) {
	Coord win = {
		st->x % bound->x,
		st->y % bound->y
	};

	return win;
}

int inRng(int val, int floor, int roof) {
	return val >= floor && val <= roof;
}
