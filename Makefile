SH=/bin/bash

EXEC=blit

CC=gcc

BUILDDIR=build

ODIR=o

LDFLAGS=-lGL -lGLEW -lSDL2 -lSDL2_image

SRCS=main.c col.c blit.c shader.c layout.c err.c util.c
OBJS=$(SRCS:%.c=$(BUILDDIR)/%.o)

HDRS=math.h

.PHONY: all
all: mk_build mk_o $(EXEC)

$(BUILDDIR)/%.o: %.c
	$(CC) -c $< -o $@

$(EXEC): $(OBJS) $(HDRS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: mk_o
mk_o:
	mkdir -p $(ODIR)

.PHONY: clean
clean:
	rm $(OBJS) $(EXEC)
