#include <stdbool.h>

#include "shader.h"
#include "layout.h"
#include "util.h"

extern const unsigned int res[2];

int solid() {
	return true;
}

int even(Coord* st) {
	return ((st->y * res[Y]) + st->x) % 2;
}

int rect(Coord* st, Coord* loc, Coord* dim) {
	return
		st->x > loc->x && st->x < loc->x + dim->x &&
		st->y > loc->y && st->y < loc->y + dim->y;
}

int sq(Coord* st, Coord* loc, unsigned int ln) {
	Coord dim = {
		ln,
		ln
	};

	return rect(st, loc, &dim);
}

int hStripe(unsigned int y, unsigned int thick) {
	return y % (thick * 2) > thick;
}

int vStripe(unsigned int x, unsigned int thick) {
	return x % (thick * 2) > thick;
}

int halfTri(Coord* st) {
	return st->x < st->y;
}

int quadTri(Coord* st) {
	return halfTri(st) ^ (pfpLn - st->x < st->y);
}

int sqOr(Coord* st) {
	unsigned int ln = 100;

	Coord loc[2] = {
		{
			center(pfpLn) - center(ln) - (margin * 2),
			center(pfpLn) - center(ln) - (margin * 2)
		}, {
			center(pfpLn) - center(ln) + (margin * 2),
			center(pfpLn) - center(ln) + (margin * 2)
		}
	};

	return sq(st, &loc[0], ln) || sq(st, &loc[1], ln);
}

int sqAnd(Coord* st) {
	unsigned int ln = 100;

	Coord loc[2] = {
		{
			center(pfpLn) - center(ln) - (margin * 2),
			center(pfpLn) - center(ln) - (margin * 2)
		}, {
			center(pfpLn) - center(ln) + (margin * 2),
			center(pfpLn) - center(ln) + (margin * 2)
		}
	};

	return sq(st, &loc[0], ln) && sq(st, &loc[1], ln);
}

int sqXor(Coord* st) {
	unsigned int ln = 100;

	Coord loc[2] = {
		{
			center(pfpLn) - center(ln) - (margin * 2),
			center(pfpLn) - center(ln) - (margin * 2)
		}, {
			center(pfpLn) - center(ln) + (margin * 2),
			center(pfpLn) - center(ln) + (margin * 2)
		}
	};

	return sq(st, &loc[0], ln) ^ sq(st, &loc[1], ln);
}

int diagStripe(Coord* st, unsigned int thick) {
	return (st->x + st->y) % (thick * 2) > thick;
}

int checker(Coord* st, unsigned int ln) {
	return ((st->x % ln > center(ln)) ^ (st->y % ln > center(ln)));
}

int shade(Coord* st, unsigned int lvl) {
	Coord bound = {
		pfpLn,
		pfpLn
	};

	return !(coordToIdx(st, &bound) % lvl);
}

int border(Coord* st, Coord* loc, Coord* dim, unsigned int thick) {
	Coord outerDim = {
		dim->x + (thick * 2),
		dim->y + (thick * 2)
	};

	Coord innerLoc = {
		loc->x + thick,
		loc->y + thick
	};

	return rect(st, loc, &outerDim) && !rect(st, &innerLoc, dim);
}

int stripeBorderHor(Coord* st) {
	unsigned int thick = 25;

	return
		st->y > center(pfpLn) - thick && st->y < center(pfpLn) + thick ||
		st->y > -(thick + (margin * 2)) + center(pfpLn) - margin && st->y < -(thick + (margin * 2)) + center(pfpLn) + margin ||
		st->y > (thick + (margin * 2)) + center(pfpLn) - margin && st->y < (thick + (margin * 2)) + center(pfpLn) + margin;
}

int stripeBorderVert(Coord* st) {
	unsigned int thick = 25;

	return
		st->y > center(pfpLn) - thick && st->y < center(pfpLn) + thick ||
		st->y > -(thick + (margin * 2)) + center(pfpLn) - margin && st->y < -(thick + (margin * 2)) + center(pfpLn) + margin ||
		st->y > (thick + (margin * 2)) + center(pfpLn) - margin && st->y < (thick + (margin * 2)) + center(pfpLn) + margin;
}
