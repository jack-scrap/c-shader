CC=gcc

LDFLAGS+=-lGL -lGLEW
LDFLAGS+=-lSDL2

.PHONY: clean

all: make

main.o: main.c
	$(CC) -c $< -o $@

make: main.o
	$(CC) $^ $(LDFLAGS)

clean:
	rm *.o a.out
