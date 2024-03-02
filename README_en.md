
# Game of Life

## Project Overview

The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning its evolution is determined by its initial state, requiring no further input from human players. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.

## Rules of the Game

The game is played on an infinite, two-dimensional grid of square cells, each of which is in one of two possible states, alive or dead. For each cell, its state in the next generation is determined by a set of rules related to the states of neighboring cells:

1. **Birth:** A dead cell with exactly three live neighbors becomes a live cell (as if by reproduction).
2. **Survival:** A live cell with two or three live neighbors stays alive for the next generation.
3. **Death:** A live cell with fewer than two live neighbors dies from underpopulation, and a live cell with more than three live neighbors dies from overpopulation. Similarly, a dead cell with any number of live neighbors other than three remains dead.

These simple rules lead to a wide variety of outcomes, with certain initial patterns leading to infinite growth, oscillation, or eventual death.

## Purpose of the Project

This recreation in the C language aims to implement the core functionality of the Game of Life, allowing users to input initial configurations and observe the evolution of the system according to Conway's rules.

## Setup Instructions

### Prerequisites

- Ensure that **gcc** and **make** utilities are installed on your system.
- Download the [Cairo GUI lib](https://www.cairographics.org/).

### Compiling the Program

After cloning the repository, use the **make** command to compile the source code.

### Setting up Your Initial Game Config

You can set up your initial configuration for a given simulation in a text file. This file will determine which cells are alive when the simulation begins. Follow these steps to create your configuration file:

#### 1. Choose Your Grid Size

The first line of your configuration file should specify the size of the grid. Enter two numbers separated by a space: the first number for the number of rows, and the second for the number of columns.

For example, to create a 10x12 grid, write:
```
10 12
```

#### 2. Specify Live Cells

After setting the grid size, list the coordinates of the cells you want to start as alive. Each cell is specified by a pair of numbers on a new line, representing its row and column. The top-left corner of the grid is considered the origin, at coordinates (1, 1).

If you want a cell at row 5, column 5 to be alive, add this line next:
```
5 5
```

Repeat this step for each cell you want to start alive. If you have multiple cells, list each on a new line.

#### 3. Indicate the End of Your Configuration

After listing all your live cells, add a single `0` on a new line. This signals the end of your configuration.

For example, if you want to initialize a small pattern, your configuration file might look like this:
```
10 12

5 5
6 5
7 5

0
```

This configuration creates a 10x12 grid with three cells in a vertical line starting from (5, 5).

#### Final Notes

- Make sure there are no extra spaces or lines after the final `0`.
- Save your file with a `.txt` extension.

### Running the Program

With the initial configuration file written, you can now run the program with the said configuration file.

```bash
./bin/final <config_file.txt>
```

### How to Play

- Use the left mouse button to advance the game.
- Activate additional features displayed under the grid by pressing the specified buttons on your keyboard.
