train.o:
	g++ src/train.cpp -o bin/train.o

terminal.o:
	g++ src/terminal.cpp -o bin/terminal.o

window.o:
	g++ src/window.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wno-narrowing -o bin/window.o

