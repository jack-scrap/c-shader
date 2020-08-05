ogl = -lGL -lGLEW
sdl = -lSDL2 -lSDL2_ttf

make: main.cpp
	g++ main.cpp $(ogl) $(sdl)
