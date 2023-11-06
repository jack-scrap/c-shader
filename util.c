#include "util.h"

unsigned int coordToIdx(Coord st, Coord bound) {
	return (st.y * bound.x) + st.x;
}
