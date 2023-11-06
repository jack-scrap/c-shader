#include <stdbool.h>

#include "shader.h"
#include "layout.h"

extern const unsigned int res[2];

int solid() {
	return true;
}

int even(Coord st) {
	return ((st.y * res[Y]) + st.x) % 2;
}

int rect(Coord st, Coord loc, Coord dim) {
	return
		st.x > loc.x && st.x < loc.x + dim.x &&
		st.y > loc.y && st.y < loc.y + dim.y;
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
	return st.x < st.y;
}

int quadTri(Coord st) {
	return halfTri(st) ^ (pfpLn - st.x < st.y);
}

int sqOr(Coord st) {
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

	return sq(st, loc[0], ln) || sq(st, loc[1], ln);
}

int sqAnd(Coord st) {
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

	return sq(st, loc[0], ln) && sq(st, loc[1], ln);
}

int sqXor(Coord st) {
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

	return sq(st, loc[0], ln) ^ sq(st, loc[1], ln);
}

int diagStripe(Coord st, unsigned int thick) {
	return (st.x + st.y) % (thick * 2) > thick;
}

int checker(Coord st, unsigned int ln) {
	return ((st.x % ln > center(ln)) ^ (st.y % ln > center(ln))) && diagStripe(st, pfpLn / 8);
}

Coord localize(Coord st, Coord bound) {
	Coord win = {
		st.x % bound.x,
		st.y % bound.y
	};

	return win;
}
