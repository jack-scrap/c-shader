#include <stdlib.h>

#include "blit.h"
#include "err.h"

int blitPix(unsigned char data[res[Y]][res[X]][CHAN_NO], Coord st, Col col) {
	if (data == NULL) {
		err(ERR_NULL_PTR);

		return 1;
	}

	if (!(st.x <= res[X] && st.y <= res[Y])) {
		err(ERR_PIXEL_COORD_BOUND);

		return 1;
	}

	data[st.y][st.x][R] = col._r;
	data[st.y][st.x][G] = col._g;
	data[st.y][st.x][B] = col._b;

	return 0;
}

int blitRect(unsigned char data[res[Y]][res[X]][CHAN_NO], Coord sz, Coord pos, Col col) {
	if (data == NULL) {
		err(ERR_NULL_PTR);

		return 1;
	}

	for (int y = 0; y < sz.y; y++) {
		for (int x = 0; x < sz.x; x++) {
			Coord st = {
				pos.x + x,
				pos.y + y
			};

			if (blitPix(data, st, col)) {
				err(ERR_BLIT_PIX);
			}
		}
	}

	return 0;
}

int clear(unsigned char data[res[Y]][res[X]][CHAN_NO]) {
	if (data == NULL) {
		err(ERR_NULL_PTR);

		return 1;
	}

	Coord origin = {
		0,
		0
	};

	Coord bound = {
		res[X],
		res[Y]
	};

	blitRect(data, bound, origin, black);

	return 0;
}
