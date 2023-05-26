SH=/bin/bash

EXEC=blit

CC=gcc

BUILDDIR=build

LDFLAGS=-lGL -lGLEW -lSDL2

SRCS=main.c

HDRS=math.h

.PHONY: all
all: mk_build $(EXEC)

$(BUILDDIR)/%.o: %.c
	$(CC) -c $< -o $@

$(EXEC): $(BUILDDIR)/main.o $(HDRS)
	$(CC) $< $(LDFLAGS) -o $@

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o $(EXEC)
