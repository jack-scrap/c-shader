#ifndef SHADER_H
#define SHADER_H

#include "math.h"

int solid();

int even(Coord st);

int rect(Coord st, Coord loc, Coord dim);

int sq(Coord st, Coord loc, unsigned int ln);

#endif
