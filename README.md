<!-- omit in toc -->
# Game Of Life

- [Description](#description)
- [Implementation](#implementation)
- [How To Build](#how-to-build)
- [To Do List](#to-do-list)


# Description


<p style="color:red;">**NOTE**: THIS DOCUMENT IS STILL WORK IN PROGRESS</p>

The **Game Of Life**, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine. (*from [Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)*)


# Implementation

This is a simplified sequence of events when the application is started:

1. `main.cpp`:
    - The `main` function instantiates the `Backend` class, which will be the only one that can interact with the QML front-end.
    - A QML engine, `QQmlApplicationEngine`, is created.
    - From the QML engine, a `QQmlContext` is obtained.
    - The context is used to set the `Backend` instance as a context property of the engine. That is, from now on the `Backend` class can interact with the QML front-end, by using the `backend` keyword in any QML document (`backend` has now global visibility in QML).
    - The engine loads the entry point of the QML front-end, `Main.qml`.
2. `Main.qml`:
    - A root container (`rootContainer`) is created. It is necessary because the `ApplicationWindow` does not have `states`.
    - A `Loader` is created. The `Loader` will be used to dynamically load the Welcome screen first, and the Game Board second. The `Loader` is governed by the `states` of the `rootContainer`.
3. `WelcomeScreen.qml`
    - This file is loaded by default, because it is tied to the default `state` of `rootContainer`.
    - To avoid cluttering this QML document, the game options are managed by an external QML document, `GameOptions.qml`.
4. `GameOptions.qml`
    - Here, the user can modify the game's default properties (game options).
    - When the user modifies a value, this is immediately communicated to the back-end via the `backend` keyword.
5. `WelcomeScreen.qml`
    - When the user clicks on the "Start Game" button, the button informs the `backend` that a state change has been requested. `backend` changes the state and emits an appropriate signal, which is in turn caught by `Main.qml`. Therefore, `Loader` can load `GameBoard.qml`.
6. `GameBoard.qml`
    - This QML document reads the values typed in earlier by the user, if any (otherwise, it will use the defaults, which are defined in `backend.h`)
    - The values are used to instantiate the Game Board, first as a visual element, and then as a C++ back-end in the `Component.onCompleted` section.
    - The user can click on any dead cell on the Game Board to revive it.
    - When the user is satisfied with the selection, the evolution can start by pressing the "Start Game" button.

Communication with the backend from QML to C++ and vice-versa is always and exclusively managed via the `backend` instance.


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
- Add the possibility to select multiple squares in the game board by clicking and dragging the mouse over the board.
- Refactor the code to favour readability.
- Add automatic calculation to avoid having an excessively large (i.e., out of screen) game board.
- In `Backend`, evaluate which methods should be `Q_INVOKABLE` or `public slots`.
- Decide whether the `TextField`s in `GameOptions.qml` can be simplified / exported in an external QML document. There is a lot of code duplication.
- A definitive name should be chosen for the Options / Welcome Screen.
- ~~Translate Italian comments into English.~~
- ~~Document what the code is doing and why.~~
- ~~Add selectable simulation speed and square size.~~
- ~~In the welcome screen, allow the user to choose the size of the grid. Now it is hard-coded in `GameBoard.qml`.~~
- ~~Rename `Grid` class to `Board`?~~
- ~~Check the algorithm. The right-hand half of the grid does not behave correctly.~~
- ~~Add Reset button, only active when the timer is not running, to reset the board.~~
- ~~Improve Start button: it could display "running" (or something similar) when the game is running.~~
- ~~Remove unused methods and test code.~~