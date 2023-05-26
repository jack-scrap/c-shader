SH=/bin/bash

EXEC=blit

CC=gcc

BUILDDIR=build

LDFLAGS=-lGL -lGLEW -lSDL2

SRCS=main.c err.c
OBJS=$(SRCS:%.c=$(BUILDDIR)/%.o)

HDRS=math.h col.h

.PHONY: all
all: mk_build $(EXEC)

$(BUILDDIR)/%.o: %.c
	$(CC) -c $< -o $@

$(EXEC): $(OBJS) $(HDRS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm $(OBJS) $(EXEC)
