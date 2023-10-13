#include <stdbool.h>

#include "shader.h"
#include "layout.h"
#include "util.h"

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

int dotGrid(Coord st, unsigned int stride) {
	return !(st._x % stride || st._y % stride);
}

int border(Coord st, Coord loc, Coord dim, unsigned int thick) {
	Coord innerLoc = {
		thick + loc._x,
		thick + loc._y
	};

	Coord innerDim = {
		dim._x - (thick * 2),
		dim._y - (thick * 2)
	};

	return
		rect(st, loc, dim) &&
		!rect(st, innerLoc, innerDim);
}

int hBar(Coord st, unsigned int x, unsigned int thick) {
	unsigned int half = center(thick);

	return inRng(x, st._x - half, st._x + half);
}

int vBar(Coord st, unsigned int y, unsigned int thick) {
	unsigned int half = center(thick);

	return inRng(y, st._y - half, st._y + half);
}

int se(Coord st) {
	unsigned int thick = 50;

	return hBar(st, 100, thick) || vBar(st, 100, thick);
}

int tri(Coord st, unsigned int ln) {
	return st._x + st._y < ln;
}
