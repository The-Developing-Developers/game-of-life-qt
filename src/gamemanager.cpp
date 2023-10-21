#include <QDebug>
#include "gamemanager.hpp"

GameManager::GameManager(QObject *parent)
  : QObject           (parent)
  , m_gameOptions     (new GameOptions)
  , m_gameBoard       (new GameBoard(*this))
  , m_gameStateMachine(new GameStateMachine(*this))
  , m_shapes          (new Shapes)
  , m_isAnimationAllowed(true)
{;}


GameManager::~GameManager(void)
{;}


void GameManager::resizeGameBoard(void)
{
  m_gameBoard->resizeGameBoard();
}


int GameManager::getShapeIndex(void) const
{
  return 0;
}


void GameManager::setShapeIndex(int index)
{
  m_shapes->setShapeIndex(index);
  setNumOfRows(m_shapes->getCurrentShapeNumOfRows());
  setNumOfCols(m_shapes->getCurrentShapeNumOfCols());
  resizeGameBoard();
  m_gameBoard->setCurrentShape(m_shapes->getCurrentShapeMatrix());
  boardChanged();
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


const QStringList GameManager::getListOfShapes(void) const
{
  return m_shapes->getListOfShapes();
}


void GameManager::setNumOfRows(int numOfRows)
{
  m_gameOptions->setNumOfRows(numOfRows);
  resizeGameBoard();
  numOfRowsChanged(numOfRows);
}


void GameManager::setNumOfCols(int numOfCols)
{
  m_gameOptions->setNumOfCols(numOfCols);
  resizeGameBoard();
  numOfColsChanged(numOfCols);
}


void GameManager::setTimerPeriod(int timerPeriod_ms)
{
  m_gameOptions->setTimerPeriod(timerPeriod_ms);
  timerPeriodChanged(timerPeriod_ms);
}


void GameManager::setSquareSize(int squareSize)
{
  m_gameOptions->setSquareSize(squareSize);
  squareSizeChanged(squareSize);
}


void GameManager::setSquareSpacing(int squareSpacing)
{
  m_gameOptions->setSquareSpacing(squareSpacing);
  squareSpacingChanged(squareSpacing);
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