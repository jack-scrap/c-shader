#ifndef COL_H
#define COL_H

#include <stdint.h>

enum {
	R,
	G,
	B,
	A
} chan_t;

typedef struct {
	unsigned int _r;
	unsigned int _g;
	unsigned int _b;
	unsigned int _a;
} Col;

extern uint32_t rmask;
extern uint32_t gmask;
extern uint32_t bmask;
extern uint32_t amask;

extern Col black;

extern Col red;

#endif
