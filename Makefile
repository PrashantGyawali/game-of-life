SOURCES = ./src/game.cpp ./src/grid/grid.cpp ./src/simulation/simulation.cpp

default:
	g++ $(SOURCES) -o ./build/game.exe -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm 
	./build/game.exe