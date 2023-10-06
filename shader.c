#include <stdbool.h>

#include "shader.h"

extern const unsigned int res[2];

int solid() {
	return true;
}

int even(Coord st) {
	return ((st._y * res[Y]) + st._x) % 2;
}

int rect(Coord st, Coord start, Coord dim) {
	return
		st._x > start._x && st._x < start._x + dim._x &&
		st._y > start._y && st._y < start._y + dim._y;
}
