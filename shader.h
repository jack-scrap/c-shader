#ifndef SHADER_H
#define SHADER_H

#include "math.h"

int solid();

int even(Coord* st);

int rect(Coord* st, Coord* loc, Coord* dim);

int sq(Coord* st, Coord* loc, unsigned int ln);

int hStripe(unsigned int y, unsigned int thick);

int vStripe(unsigned int x, unsigned int thick);

int halfTri(Coord* st);

int quadTri(Coord* st);

int sqOr(Coord* st);

int sqAnd(Coord* st);

int sqXor(Coord* st);

int shade(Coord* st, unsigned int lvl);

int border(Coord* st, Coord* loc, Coord* dim, unsigned int thick);

int stripeBorderHor(Coord* st);

int stripeBorderVert(Coord* st);

#endif
