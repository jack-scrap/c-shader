SH=/bin/bash

EXEC=blit

CC=gcc

BUILDDIR=build

LDFLAGS=-lGL -lGLEW -lSDL2

.PHONY: all
all: mk_build make

$(BUILDDIR)/main.o: main.c
	$(CC) -c $< -o $@

.PHONY: make
make: $(BUILDDIR)/main.o math.h
	$(CC) $< $(LDFLAGS) -o $(EXEC)

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o $(EXEC)
