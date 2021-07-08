CXX=g++

LDFLAGS+=-lGL -lGLEW
LDFLAGS+=-lSDL2

.PHONY: clean

all: make

main.o: main.cpp
	$(CXX) -c $< -o $@

make: main.o
	$(CXX) $^ $(LDFLAGS)

clean:
	rm *.o a.out
