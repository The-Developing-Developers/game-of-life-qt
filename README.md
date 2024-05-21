<!-- omit in toc -->
# John Conway's Game Of Life

- [Description](#description)
- [Download (Windows Only)](#download-windows-only)
- [Implementation](#implementation)
- [How To Build (Windows / Linux)](#how-to-build-windows--linux)
- [To Do List](#to-do-list)


# Description

**John Conway's Game Of Life**, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine. (*from [Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)*)

This is a simple graphical application that implements the rules of John Conway's Game Of Life.


# Download (Windows Only)

The executable for Windows can be downloaded from the [Releases](https://github.com/The-Developing-Developers/game-of-life-qt/releases) page. The latest release is 1.0.2.

- Windows 10 or later is required.
- Download and unpack the ZIP archive.
- Launch `gameOfLife.exe`.
- You might need to (re)install the latest Microsoft Visual C++ Redistributable in order for the executable to start properly.


# Implementation

This is a simplified sequence of events when the application is started:

1. `main.cpp`:
    - The `main` function instantiates the `GameManager` class, which will be the only one that can interact with the QML front-end.
    - A QML engine, `QQmlApplicationEngine`, is created.
    - From the QML engine, a `QQmlContext` is obtained.
    - The context is used to set the `GameManager` instance as a context property of the engine. That is, from now on the `GameManager` class can interact with the QML front-end, by using the `gameManager` keyword in any QML document (`gameManager` has now global visibility in QML).
    - The engine loads the entry point of the QML front-end, `Main.qml`.
2. `Main.qml`:
     - A `Loader` is created. The `Loader` will be used to dynamically load the `WelcomeScreen` first, and the `GameBoard` second. The `Loader` is governed by the value of its `source` property, which in turn is governed by two boolean values, `isGameActive` and `resetGameBoard`.
3. `WelcomeScreen.qml`
    - Welcomes the users, and also contains the game options.
    - To avoid cluttering this QML document, the game options are managed by an external QML document, `GameOptions.qml`.
4. `GameOptions.qml`
    - Here, the user can modify the game's default properties (game options).
    - When the user modifies a value, this is immediately communicated to the back-end via the `gameManager` keyword.
5. `WelcomeScreen.qml`
    - When the user clicks on the "Start Game" button, the button asserts `isGameActive`. As a consequence, this change is received by the `Loader` in `Main.qml`, which can therefore load `GameBoard.qml`.
6. `GameBoard.qml`
    - This QML document instantiates `CustomScrollView`, which is the actual game grid.
    - `CustomScrollView` reads the `GameOptions` indirectly, through the `gameManager`.
    - The user can click on any dead cell on the Game Board to revive it.
    - When the user is satisfied with the selection, the evolution can start by pressing the "Start Game" button.
    - The users can pause the simulation at any time and go back to the "game options" screen to make any desired change. When the users go back to the game screen, the game will "remember" the previous state of the simulation.

Communication with the backend from QML to C++ and vice-versa is always and exclusively managed via the `gameManager` instance.


# How To Build (Windows / Linux)

1. Clone this repository.
2. Install Qt 6.5 (or later version) using the web installer. Required packages:
     - C++ compiler (at least C++14)
     - Qt Creator 11.0.2 (or later version)
     - CMake 3.16 (or later version)
     - Ninja 1.10.2 (or later version)
3. Open Qt Creator.
4. Open `CMakeLists.txt`.
5. Select *Release* configuration.
6. Run.


# To Do List

- Check the `TODO`s in the code, and consider opening dedicated issues.
- Do not use a simple `bool` to manage the game state (`isGameActive` QML property). Consider using a more sophisticated system (enumeratives, or re-enabling the original FSM), in order to accommodate a potential third or fourth state in the future if the need arises.
- Consider comparing `GameManager` to the *Mediator* programming pattern, and evaluate if `GameManager` can be fully transformed into a *Mediator*.
- Consider unifying the concept of game board square and `Cell` in the code.
- A definitive name should be chosen for the Options / Welcome Screen.
- Add the option ~~to enable / disable the cell animation, and~~ to set the percentage with respect to the game timer period.
- Consider adding Doxygen documentation, using Graphviz to generate the structure of the C++ classes.
- Consider adding the executable for download (using [CPack](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Packaging%20With%20CPack.html)?).

<!--
## Done

- ~~Consider if GameStateMachine and other classes should be singletons~~
- ~~The automatic stop is probably inefficient, because it checks for equality between the `m_currentMatrix` and the `m_nextMatrix` at every game loop. Should a timer be used to rarify the checks?~~
- ~~Now that the FSM receives the `gameManager` by reference, should the FSM be directly responsible of carrying out back-end actions such as reinitialising the game board? Or is it better that the FSM just informs the `GameManager` that the `GameManager` has to perform a certain action, and the `GameManager` actually carries out that action?~~
- ~~The name of the `Patterns::setPatternIndex` method is poorly chosen, because it does much more than setting the current pattern's index. Consider changing the name, and even refactoring the whole function, maybe splitting it into smaller functions.~~
- ~~- Fix the centering of the Game Board when the user selects a shape through the Combo Box.~~
~~- A pop-up selector of shapes has been implemented in the Game Board. However, we could not find a way to directly connect `gameManager.listOfPatterns` to the `ShapesModel`, unlike the `ComboBox` in `GameBoard.qml`, which accepts `gameManager.listOfPatterns` as a `model` without any issues. Therefore, a dedicated model has been created in QML, `ShapesModel.qml`. This solutions works correctly, but it duplicates the maintenance of the list of shapes, that now are defined both in C++ (in `patterns.hpp`). There should be a way to associate a simple `QStringList` as a model of a `ListView`.~~
- ~~Consider using an `onEditingFinished` instead of `onAccepted` for convenience in `GameOptions.qml` for the option buttons. However, automatic focus on the "number of rows" `CustomTextField` must be removed, because going back to the Options screen triggers an undesired modification if `onEditingFinished` is used: the rows are changed to the minimum value.~~
- ~~Consider using the `Validator` feature of the `TextField` to limit the values of the Game Options instead of clamping manually in the setter methods in the backend.~~
- ~~- Implement an upper limit for the Game Options (i.e., the user cannot request a Game Board with millions of rows or columns).~~
- ~~There is a small bug when the user turns on some cells, resizes the board using the combo box, goes back to the Welcome Screen, enlarges the Game Board, and starts the game again: some cells that were previously ON are now OFF.~~
- ~~Consider using an asymmetrical fading effect (i.e. only a fade-in, not a fade-out) for better visibility of the toggling of the cells across generations while using fast game speed.~~
- ~~Allow the user to disable the fading effect on the cells.~~
- ~~Implement an automatic stop once there is no change between the `m_currentMatrix` and the `m_futureMatrix`.~~
- ~~Add a couple more helper private methods in `gameboard.cpp` to make the code more readable in `calculateFutureMatrix`.~~
- ~~Consider not clearing the board even if the user goes back to the options and modifies the game board's size. To do this, especially in case the board is shrinked, it is necessary to memorise (save) the cells' status (alive or dead) and reinstate (load) it when a game board of a different size is created. Maybe a vector of `bool` is sufficient: the indices of the vector could correspond to the indices of the recreated game board's matrix. To help with this, consider not destroying the game board when a new game is started, but simply to resize the vector of vectors of `Cell`s whenever the number of rows or columns is modified through the game options.~~
- ~~Decide whether the `TextField`s in `GameOptions.qml` can be simplified / exported in an external QML document. There is a lot of code duplication. Even better: make QML documents leaner by creating more, smaller QML documents.~~
- ~~Add "are you sure" pop-up when the user clicks on "clear game board".~~
- ~~Consider not clearing the board if the user goes back to the options and only modifies options NOT related to the game board's size (for example, the user only wants to modify the game's speed).~~
- ~~In `Backend`, evaluate which methods should be `Q_INVOKABLE` or `public slots`.~~
- ~~`Q_PROPERTY` in `backend.h`: should they also use a `NOTIFY` signal?~~
- ~~Consider removing all `Q_PROPERTY` in `backend.h` and using only the public methods / slots / `Q_INVOKABLE` to interact between C++ and QML.~~
- ~~Use smart pointers instead of raw pointers for the `Cell**` matrices?~~
- ~~Use Qt's `QScopedPointer` and `<QVector>` instead of unique pointers and `std::vector`?~~
- ~~Is `Backend` class unnecessary? Could it be merged with `GameBoard`? There is a lot of duplicated code.~~ No, it is not unnecessary: creating the `GameOptions` class has removed a lot of duplications.
- ~~Should the game options be migrated from the `Backend` to a new, dedicated `GameOptions` class? This could remove some duplication between `Backend` and `GameBoard`.~~
- ~~`m_hasJustBeenToggled` data member is temporarily set manually from the outside, but it will need to be set via a proper setter, and made `private`.~~
- ~~Should the `Backend` implement a finite-state machine to manage the states? This would relieve the front-end (`GameBoard.qml`) of the responsibility to instantiate a new game board via the `initialiseBoard` method. The main idea would be to only request game state changes from the front-end, which would therefore be completely agnostic of how the various classes are instantiated. The `Backend` would then create a new `GameBoard` every time a new game is started, and destroy it whenever the user decides to go back to the welcome screen, because if the user decides to modify the game board's size and restart, it is necessary to reallocate the two `Cell**` matrices in `GameBoard`.~~
- ~~Allow the user to choose the spacing between the cells in the Game Board.~~
- ~~Add automatic calculation to avoid having an excessively large (i.e., out of screen) game board.~~
- ~~Add the possibility to select multiple squares in the game board by clicking and dragging the mouse over the board.~~
- ~~Translate Italian comments into English.~~
- ~~Document what the code is doing and why.~~
- ~~Add selectable simulation speed and square size.~~
- ~~In the welcome screen, allow the user to choose the size of the grid. Now it is hard-coded in `GameBoard.qml`.~~
- ~~Rename `Grid` class to `Board`?~~
- ~~Check the algorithm. The right-hand half of the grid does not behave correctly.~~
- ~~Add Reset button, only active when the timer is not running, to reset the board.~~
- ~~Improve Start button: it could display "running" (or something similar) when the game is running.~~
- ~~Remove unused methods and test code.~~ -->