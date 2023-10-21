#include <stdbool.h>

#include "shader.h"

extern const unsigned int res[2];

int solid() {
	return true;
}

int even(Coord st) {
	return ((st._y * res[Y]) + st._x) % 2;
}

int rect(Coord st, Coord loc, Coord dim) {
	return
		st._x > loc._x && st._x < loc._x + dim._x &&
		st._y > loc._y && st._y < loc._y + dim._y;
}

int sq(Coord st, Coord loc, unsigned int ln) {
	Coord dim = {
		ln,
		ln
	};

	return rect(st, loc, dim);
}

int hStripe(unsigned int y, unsigned int thick) {
	return y % (thick * 2) > thick;
}

int vStripe(unsigned int x, unsigned int thick) {
	return x % (thick * 2) > thick;
}

int halfTri(Coord st) {
	return st._x < st._y;
}

Coord localize(Coord st, Coord bound) {
	Coord win = {
		st._x % bound._x,
		st._y % bound._y
	};

	return win;
}
