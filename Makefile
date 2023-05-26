SH=/bin/bash

EXEC=blit

CC=gcc

BUILDDIR=build

LDFLAGS=-lGL -lGLEW -lSDL2

.PHONY: all
all: mk_build $(EXEC)

$(BUILDDIR)/main.o: main.c
	$(CC) -c $< -o $@

$(EXEC): $(BUILDDIR)/main.o math.h
	$(CC) $< $(LDFLAGS) -o $@

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o $(EXEC)
