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

int diagStripe(Coord* st, unsigned int thick);

int checker(Coord* st, unsigned int ln);

int shade(Coord* st, unsigned int lvl);

int border(Coord* st, Coord* loc, Coord* dim, unsigned int thick);

int stripeBorderHor(Coord* st);

int stripeBorderVert(Coord* st);

int x(Coord* st);

#endif
