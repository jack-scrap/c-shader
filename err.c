#include <stdio.h>

#include "err.h"

void err(err_t e) {
	switch (e) {
		case ERR_NULL_PTR:
			fprintf(stderr, "%s\n", "Attempt to operate on null pointer");

			break;

		case ERR_PIXEL_COORD_BOUND:
			fprintf(stderr, "%s\n", "Pixel coordinate out of bounds");

			break;

		case ERR_BLIT_PIX:
			fprintf(stderr, "%s\n", "Couldn't blit pixel");

			break;

		case ERR_ENUM_INVALID:
			fprintf(stderr, "%s\n", "Invalid enumeration");

			break;

		default:
			err(ERR_ENUM_INVALID);

			break;
	};
}
