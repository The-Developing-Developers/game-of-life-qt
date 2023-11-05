#include <QDebug>
#include "gamemanager.hpp"

GameManager::GameManager(QObject *parent)
  : QObject           (parent)
  , m_gameOptions     (new GameOptions)
  , m_gameBoard       (new GameBoard(*this))
  , m_patterns          (new Patterns)
  , m_isAnimationAllowed(true)
{;}


GameManager::~GameManager(void)
{;}


void GameManager::resizeGameBoard(void)
{
  m_gameBoard->resizeGameBoard();
}


int GameManager::getPatternIndex(void) const
{
  return 0;
}


void GameManager::setCurrentPattern(int index)
{
  if (index == 0 || index == 6 || index == 12)
    return; // separators in the combo box (i.e., do nothing)

  m_patterns->setPatternIndex(index);
  setNumOfRows(m_patterns->getCurrentPatternNumOfRows());
  setNumOfCols(m_patterns->getCurrentPatternNumOfCols());
  resizeGameBoard();
  m_gameBoard->setCurrentPattern(m_patterns->getCurrentPatternMatrix());
  emit boardChanged();
}


void GameManager::clearBoard(void)
{
  m_gameBoard->clearBoard();
  emit boardChanged();
}


void GameManager::recalculateBoard(void)
{
  m_gameBoard->recalculateBoard();
  emit boardChanged();
}


bool GameManager::getCellStatus(int cellIndex) const
{
  return m_gameBoard->getCellStatus(cellIndex);
}


const QStringList GameManager::getListOfPatterns(void) const
{
  return m_patterns->getListOfPatterns();
}


int GameManager::getMinNumOfRowsAndCols(void) const
{
  return m_gameOptions->getMinNumOfRowsAndCols();
}


int GameManager::getMaxNumOfRowsAndCols(void) const
{
  return m_gameOptions->getMaxNumOfRowsAndCols();
}


int GameManager::getMinTimerPeriod_ms(void) const
{
  return m_gameOptions->getMinTimerPeriod_ms();
}


int GameManager::getMaxTimerPeriod_ms(void) const
{
  return m_gameOptions->getMaxTimerPeriod_ms();
}


int GameManager::getMinSquareSize(void) const
{
  return m_gameOptions->getMinSquareSize();
}


int GameManager::getMaxSquareSize(void) const
{
  return m_gameOptions->getMaxSquareSize();
}


int GameManager::getMinSquareSpacing(void) const
{
  return m_gameOptions->getMinSquareSpacing();
}


int GameManager::getMaxSquareSpacing(void) const
{
  return m_gameOptions->getMaxSquareSpacing();
}


void GameManager::setNumOfRows(int numOfRows)
{
  m_gameOptions->setNumOfRows(numOfRows);
  resizeGameBoard();
  emit numOfRowsChanged(numOfRows);
}


void GameManager::setNumOfCols(int numOfCols)
{
  m_gameOptions->setNumOfCols(numOfCols);
  resizeGameBoard();
  emit numOfColsChanged(numOfCols);
}


void GameManager::setTimerPeriod(int timerPeriod_ms)
{
  m_gameOptions->setTimerPeriod(timerPeriod_ms);
  emit timerPeriodChanged(timerPeriod_ms);
}


void GameManager::setSquareSize(int squareSize)
{
  m_gameOptions->setSquareSize(squareSize);
  emit squareSizeChanged(squareSize);
}


void GameManager::setSquareSpacing(int squareSpacing)
{
  m_gameOptions->setSquareSpacing(squareSpacing);
  emit squareSpacingChanged(squareSpacing);
}


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


void GameManager::backgroundInteracted(int mouseX, int mouseY)
{
  m_gameBoard->toggleCellStatusBecauseOfMouseInteraction(mouseX, mouseY);
  emit boardChanged();
}


void GameManager::backgroundReleased(void)
{
  m_gameBoard->unlockToggling();
}


GameOptions& GameManager::getGameOptions(void) const
{
  return *m_gameOptions;
}


void GameManager::stopTheTimer(void)
{
  emit stopTimer();
}
