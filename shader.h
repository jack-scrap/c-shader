#ifndef SHADER_H
#define SHADER_H

#include "math.h"

int solid();

int even(Coord st);

int rect(Coord st, Coord loc, Coord dim);

int sq(Coord st, Coord loc, unsigned int ln);

int hStripe(unsigned int y, unsigned int thick);

int vStripe(unsigned int x, unsigned int thick);

int dotGrid(Coord st, unsigned int stride);

#endif
