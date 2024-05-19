/**
 * @file gamemanager.cpp
 *
 * @brief The methods defined here are mostly forwarding to or getting information from other classes, such as 'GameBoard' or 'GameOptions'.
 **/

#include <QDebug>
#include "gamemanager.hpp"

GameManager::GameManager(QObject *parent)
  : QObject           (parent)
  , m_gameOptions     (new GameOptions)
  , m_gameBoard       (new GameBoard(*this))
  , m_patterns        (new Patterns)
  , m_isAnimationAllowed(true)
{;}


GameManager::~GameManager(void)
{;}


/**
 * @brief The `GameManager` already instantiates a `Patterns` object in its constructor. Therefore, we can use that instance instead of
 * creating a new one to pass to the QML front-end.
 *
 * @return Raw `Patterns*` to be passed to the QML front-end through `setContextProperty`.
 **/
Patterns* GameManager::getPatternPointerForQmlContext(void) const
{
  return m_patterns.data();
}


/**
 * @brief Called every time the board needs to be resized, for example because the user has specified a different number of rows, columns,
 * or has chosen a particular shape from the shape selector.
 **/
void GameManager::resizeGameBoard(void)
{
  m_gameBoard->resizeGameBoard();
}


/**
 * @brief Never used by the QML front-end. Only defined for completeness (`Q_PROPERTY currentPatternIndex`)
 **/
int GameManager::getPatternIndex(void) const
{
  return 0; // TODO: update 'Patterns' and return 'getPatternIndex' here instead of 0
}


/**
 * @brief Receives the index of the shape pattern chosen by the user and communicates it to `Patterns`, which calculates the new pattern
 * matrix. Then, the game grid can be properly resized by `m_gameBoard`.
 **/
void GameManager::setCurrentPattern(int index)
{
  if (index == 0 || index == 6 || index == 12) // TODO: Find a better way to filter the indices that should do nothing in `GameManager::setCurrentShape`. `GameManager` should know nothing about the numeric indices of the separators, and yet it should still be able to do nothing if a separator is selected. Maybe perform a check in `GameBoard.qml` before assigning `gameManager.currentShapeIndex` in `ComboBox`? Maybe use enumeratives instead of integers to skip the separators in the `ListView`?
    return; // The user has mistakenly chosen a separator instead of a shape pattern in the ListView (i.e., do nothing)

  m_patterns->setPatternIndex(index);
  setNumOfRows(m_patterns->getCurrentPatternNumOfRows());
  setNumOfCols(m_patterns->getCurrentPatternNumOfCols());
  resizeGameBoard();
  m_gameBoard->setCurrentPattern(m_patterns->getCurrentPatternMatrix());
  emit boardChanged();
}


/**
 * @brief Called by the QML front-end when the user requests to clear the game board. In the back-end, all the cells are "killed".
 **/
void GameManager::clearBoard(void)
{
  m_gameBoard->clearBoard();
  emit boardChanged();
}


/**
 * @brief Called by the QML front-end whenever the game timer expires.
 **/
void GameManager::recalculateBoard(void)
{
  m_gameBoard->recalculateBoard();
  emit boardChanged();
}


/**
 * @brief Called by the QML front-end to determine how a cell should be coloured (dead or alive).
 **/
bool GameManager::getCellStatus(int cellIndex) const
{
  return m_gameBoard->getCellStatus(cellIndex);
}


// // TODO: unused --> remove
// const QStringList GameManager::getListOfPatterns(void) const
// {
//   return m_patterns->getListOfPatterns();
// }


/**
 * @brief Called by the QML front-end in the setup screen, to validate user's input
 **/
int GameManager::getMinNumOfRowsAndCols(void) const
{
  return m_gameOptions->getMinNumOfRowsAndCols();
}


/**
 * @brief Called by the QML front-end in the setup screen, to validate user's input
 **/
int GameManager::getMaxNumOfRowsAndCols(void) const
{
  return m_gameOptions->getMaxNumOfRowsAndCols();
}


/**
 * @brief Called by the QML front-end in the setup screen, to validate user's input
 **/
int GameManager::getMinTimerPeriod_ms(void) const
{
  return m_gameOptions->getMinTimerPeriod_ms();
}


/**
 * @brief Called by the QML front-end in the setup screen, to validate user's input
 **/
int GameManager::getMaxTimerPeriod_ms(void) const
{
  return m_gameOptions->getMaxTimerPeriod_ms();
}


/**
 * @brief Called by the QML front-end in the setup screen, to validate user's input
 **/
int GameManager::getMinSquareSize(void) const
{
  return m_gameOptions->getMinSquareSize();
}


/**
 * @brief Called by the QML front-end in the setup screen, to validate user's input
 **/
int GameManager::getMaxSquareSize(void) const
{
  return m_gameOptions->getMaxSquareSize();
}


/**
 * @brief Called by the QML front-end in the setup screen, to validate user's input
 **/
int GameManager::getMinSquareSpacing(void) const
{
  return m_gameOptions->getMinSquareSpacing();
}


/**
 * @brief Called by the QML front-end in the setup screen, to validate user's input
 **/
int GameManager::getMaxSquareSpacing(void) const
{
  return m_gameOptions->getMaxSquareSpacing();
}


/**
 * @brief Called by the QML front-end to set the number of rows that the game grid should have, either when the user specifies it in the
 * game options, or when a pattern shape has been selected with the shape selector.
 **/
void GameManager::setNumOfRows(int numOfRows)
{
  m_gameOptions->setNumOfRows(numOfRows);
  resizeGameBoard();
  emit numOfRowsChanged(numOfRows);
}


/**
 * @brief Called by the QML front-end to set the number of columns that the game grid should have, either when the user specifies it in the
 * game options, or when a pattern shape has been selected with the shape selector.
 **/
void GameManager::setNumOfCols(int numOfCols)
{
  m_gameOptions->setNumOfCols(numOfCols);
  resizeGameBoard();
  emit numOfColsChanged(numOfCols);
}


/**
 * @brief Called by the QML front-end to set the game speed the user specifies in the game options.
 **/
void GameManager::setTimerPeriod(int timerPeriod_ms)
{
  m_gameOptions->setTimerPeriod(timerPeriod_ms);
  emit timerPeriodChanged(timerPeriod_ms);
}


/**
 * @brief Called by the QML front-end to set the square size the user specifies in the game options.
 **/
void GameManager::setSquareSize(int squareSize)
{
  m_gameOptions->setSquareSize(squareSize);
  emit squareSizeChanged(squareSize);
}


/**
 * @brief Called by the QML front-end to set the spacing between the squares in the grid. Specified by the user in the game options.
 **/
void GameManager::setSquareSpacing(int squareSpacing)
{
  m_gameOptions->setSquareSpacing(squareSpacing);
  emit squareSpacingChanged(squareSpacing);
}


/**
 * @brief Called by the QML front-end to allow or disallow the gradual colour transition of a game cell between dead and alive state.
 * Specified by the user in the game options.
 **/
void GameManager::setIsAnimationAllowed(bool isAnimationAllowed)
{
  m_isAnimationAllowed = isAnimationAllowed;
}


int GameManager::getNumOfRows(void) const
{
  return m_gameOptions->getNumOfRows();
}


int GameManager::getNumOfCols(void) const
{
  return m_gameOptions->getNumOfCols();
}


int GameManager::getTimerPeriod(void) const
{
  return m_gameOptions->getTimerPeriod();
}


int GameManager::getSquareSize(void) const
{
  return m_gameOptions->getSquareSize();
}


int GameManager::getSquareSpacing(void) const
{
  return m_gameOptions->getSquareSpacing();
}


bool GameManager::getIsAnimationAllowed(void) const
{
  return m_isAnimationAllowed;
}


/**
 * @brief Called by the QML front-end whenever the user interacts with the game grid. This is used to overcome a limitation of Qt's
 * management of mouse clicks: when a Qt Widget such as a rectangle (which is used to represent a game cell) acquires the mouse, for example
 * because it receives a mouse click, it will not release the mouse until another event happens, such as the release of the mouse button.
 * This prevents the user to click and drag the mouse to quickly and conveniently toggle multiple cells with a single mouse action.
 * Therefore, it was necessary to overcome this obstacle by reading the (x, y) coordinates of the mouse at the moment of the click and
 * relaying them to the back-end, in order to determine in the back-end (instead of the front-end) which cell was being clicked, and to
 * allow to click and drag to toggle multiple cells with a single click.
 **/
void GameManager::backgroundInteracted(int mouseX, int mouseY)
{
  m_gameBoard->toggleCellStatusBecauseOfMouseInteraction(mouseX, mouseY);
  emit boardChanged();
}


/**
 * @brief Companion function of `backgroundInteracted`. When the user releases the mouse button after interacting with the cells in the game
 * board, it is no longer necessary to keep the cells locked to prevent rapid-fire toggling, so they can all be released.
 **/
void GameManager::backgroundReleased(void)
{
  m_gameBoard->unlockToggling();
}


/**
 * @brief Used by `GameBoard` to create an internal reference to `GameOptions`, so that `GameBoard` can read the options and adjust the game
 * grid whenever necessary.
 **/
GameOptions& GameManager::getGameOptions(void) const
{
  return *m_gameOptions;
}


/**
 * @brief Possibly called by `GameBoard` when calculating the next iteration of the game cycle.
 *
 **/
void GameManager::stopTheTimer(void)
{
  emit stopTimer();
}
