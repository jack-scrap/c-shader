SH=/bin/bash

CC=gcc

BUILDDIR=build

LDFLAGS=-lGL -lGLEW -lSDL2

.PHONY: all
all: mk_build make

$(BUILDDIR)/main.o: main.c
	$(CC) -c $< -o $@

.PHONY: make
make: $(BUILDDIR)/main.o
	$(CC) $^ $(LDFLAGS)

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o a.out
