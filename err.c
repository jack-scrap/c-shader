#include <stdio.h>

#include "err.h"

void err(char* msg) {
	fprintf(stderr, "%s\n", msg);
}
