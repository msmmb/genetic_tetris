# Tetris genetic algorithm

Tetris genetic algorithm written in C++ based on [this](https://codemyroad.wordpress.com/2013/04/14/tetris-ai-the-near-perfect-player/) article, with some changes.

After 15 minutes of training, the AI was able to clear 16.000+ lines.

Youtube demo [here](https://youtu.be/iytFLOYbyec).

## Train de AI

If an agent better than the saved one gets generated during training, parameters are automatically updated.

```sh
git clone https://www.github.com/msmmb/genetic_tetris
cd genetic_tetris
make train.o
cd bin
./train.o
```

## Run the AI on terminal

![Alt Text](../media/terminal.gif)

```sh
git clone https://www.github.com/msmmb/genetic_tetris
cd genetic_tetris
make terminal.o
cd bin
./terminal.o
```

## Run the AI on a window

![Alt Text](../media/window.gif)

To run the AI on a window [raylib](https://www.raylib.com/) needs to be installed.

You can take/lose control of the game by pressing the `c` key.

```sh
git clone https://www.github.com/msmmb/genetic_tetris
cd genetic_tetris
make window.o
cd bin
./window.o
```
