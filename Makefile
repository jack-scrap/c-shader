ogl = -lGL -lGLEW
sdl = -lSDL2

make: main.cpp
	g++ main.cpp $(ogl) $(sdl)
