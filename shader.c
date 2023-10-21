#include <stdbool.h>
#include <math.h>

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

int checker(Coord st, unsigned int ln) {
	return (st._x % ln > ln / 2) ^ (st._y % ln > ln / 2);
}

int diagStripe(Coord st, unsigned int thick) {
	return (st._x + st._y) % (thick * 2) > thick;
}

int dotMatrix(Coord st, unsigned int stride) {
	return !(st._x % stride || st._y % stride);
}

int border(Coord st, Coord loc, Coord dim, unsigned int thick) {
	Coord innerLoc = {
		thick + loc._x,
		thick + loc._y
	};

	unsigned int border = thick * 2;
	Coord innerDim = {
		dim._x - border,
		dim._y - border
	};

	return rect(st, loc, dim) && !rect(st, innerLoc, innerDim);
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

int sine(Coord st, int freq, float amp) {
	return norm(st._y, Y) < sin(norm(st._x * M_PI * 2 * freq, X)) * 0.3;
}

int fizzBuzz(Coord st) {
	Coord bound = {
		res[X],
		res[Y]
	};

	int i = coordToIdx(st, bound);

	return !(i % 3) || !(i % 5);
}

int grid(Coord st, unsigned int stride) {
	return !(st._x % stride) || !(st._y % stride);
}

int el(Coord st, unsigned int idx) {
	unsigned int margin = 8;

	Coord loc = {
		margin + (idx * margin * 2),
		margin
	};

	return sq(st, loc, 32);
}

// Bitwise
int op_or(Coord st) {
	return st._x | st._y;
}

int op_and(Coord st) {
	return st._x & st._y;
}

int op_xor(Coord st) {
	return st._x ^ st._y;
}
