SH=/bin/bash

CC=gcc

BUILDDIR=build

LDFLAGS+=-lGL -lGLEW
LDFLAGS+=-lSDL2

.PHONY: all mk_build make clean

all: mk_build make

$(BUILDDIR)/main.o: main.c
	$(CC) -c $< -o $@

make: $(BUILDDIR)/main.o
	$(CC) $^ $(LDFLAGS)

mk_build:
	mkdir -p $(BUILDDIR)

clean:
	rm $(BUILDDIR)/*.o a.out
