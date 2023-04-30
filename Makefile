
RUN_FILES = src/utils/piece.cpp src/utils/grid.cpp src/utils/neuralNetwork.cpp src/utils/brain.cpp
TRAIN_FILES = $(RUN_FILES) src/utils/population.cpp src/utils/geneticAlgorithm.cpp
RAYLIB_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wno-narrowing

train: 
	g++ src/train.cpp $(TRAIN_FILES) -o train.o

terminal: 
	g++ src/terminal.cpp $(RUN_FILES) -o terminal.o

window: 
	g++ src/window.cpp $(RAYLIB_FLAGS) $(RUN_FILES) -o window.o

all: 
	g++ src/train.cpp $(TRAIN_FILES) -o train.o
	g++ src/terminal.cpp $(RUN_FILES) -o terminal.o
	g++ src/window.cpp $(RAYLIB_FLAGS) $(RUN_FILES) -o window.o
	