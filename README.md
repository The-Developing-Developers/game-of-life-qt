<!-- omit in toc -->
# Game Of Life

- [Description](#description)
- [Implementation](#implementation)
- [How To Build](#how-to-build)
- [To Do List](#to-do-list)


# Description


<p style="color:red;">**NOTE**: THIS DOCUMENT IS STILL WORK IN PROGRESS</p>

The [Game Of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine. (*from Wikipedia*)


# Implementation

This version of Game Of Life is being implemented in Qt Quick 6.5.


# How To Build

1. Clone this repository.
2. Install Qt 6.5 (or later version) using the web installer. Required packages:
  - C++ compiler
  - Qt Creator 11.0.2 (or later version)
  - CMake 3.24.2
  - Ninja 1.10.2
3. Open Qt Creator.
4. Open `MakeLists.txt`.
5. Select *Release* configuration.
6. Run.


# To Do List

- Is `Backend` class unnecessary? Could it be merged with `Grid`?
- Improve Start button: it could display "running" (or something similar) when the game is running.
- Add Reset button, only active when the timer is not running, to reset the board.
- Add a welcome screen to allow the user to choose the size of the grid. Now it is hard-coded in `Main.qml`.
- Add selectable simulation speed
- Translate Italian comments into English.
- Document what the code is doing and why.
- Refactor the code to favour readability.
- ~~Remove unused methods and test code.~~