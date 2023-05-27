#ifndef ERR_H
#define ERR_H

typedef enum {
	ERR_NULL_PTR,
	ERR_PIXEL_COORD_BOUND,
	ERR_BLIT_PIX
} err_t;

void err(err_t err);

#endif
