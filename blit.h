#ifndef BLIT_H
#define BLIT_H

#include "math.h"
#include "col.h"

#define CHAN_NO 3 + 1

extern const unsigned int res[2];

int blitPix(unsigned char data[res[Y]][res[X]][CHAN_NO], Coord st, Col col);

int blitRect(unsigned char data[res[Y]][res[X]][CHAN_NO], Coord sz, Coord pos, Col col);

int clear(unsigned char data[res[Y]][res[X]][CHAN_NO]);

#endif
