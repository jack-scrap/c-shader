#ifndef COL_H
#define COL_H

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

uint32_t rmask = 0xff000000;
uint32_t gmask = 0x00ff0000;
uint32_t bmask = 0x0000ff00;
uint32_t amask = 0x000000ff;

Col black = {
	0,
	0,
	0,
	255
};

Col red = {
	255,
	0,
	0,
	255
};

#endif
