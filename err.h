#ifndef ERR_H
#define ERR_H

typedef enum {
	ERR_NULL_PTR,
	ERR_PIXEL_COORD_BOUND,
	ERR_BLIT_PIX,
	ERR_ENUM_INVALID
} err_t;

void err(err_t e);

#endif
