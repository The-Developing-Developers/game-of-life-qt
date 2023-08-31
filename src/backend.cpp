#include <QDebug>
#include "backend.h"

Backend::Backend(QObject *parent)
  : QObject{parent}
{;}


Backend::~Backend(void)
{
  delete m_gameBoard;
}


void Backend::initialiseBoard(void)
{
  if (m_gameBoard != nullptr)
    delete m_gameBoard;

  m_gameBoard = new GameBoard(m_numOfRows, m_numOfCols, m_squareSize, m_squareSpacing);
}


void Backend::clearBoard(void)
{
  m_gameBoard->clearBoard();
  emit boardRecalculated();
}


void Backend::recalculateBoard(void)
{
  m_gameBoard->recalculateBoard();
  emit boardRecalculated();
}


bool Backend::getCellStatus(int cellIndex)
{
  return m_gameBoard->getCellStatus(cellIndex);
}


void Backend::setNumOfRows(int numOfRows)
{
  if (numOfRows >= m_minNumOfRowsAndCols)
    m_numOfRows = numOfRows;
  else
    m_numOfRows = m_minNumOfRowsAndCols;
}


void Backend::setNumOfCols(int numOfCols)
{
  if (numOfCols >= m_minNumOfRowsAndCols)
    m_numOfCols = numOfCols;
  else
    m_numOfCols = m_minNumOfRowsAndCols;
}


void Backend::setTimerPeriod(int timerPeriod_ms)
{
  if (timerPeriod_ms >= m_minTimerPeriod_ms)
    m_timerPeriod_ms = timerPeriod_ms;
  else
    m_timerPeriod_ms = m_minTimerPeriod_ms;
}


void Backend::setSquareSize(int squareSize)
{
  if (squareSize >= m_minSquareSize)
    m_squareSize = squareSize;
  else
    m_squareSize = m_minSquareSize;
}


int Backend::getNumOfRows(void) const
{
  return m_numOfRows;
}


int Backend::getNumOfCols(void) const
{
  return m_numOfCols;
}


int Backend::getTimerPeriod(void) const
{
  return m_timerPeriod_ms;
}


int Backend::getSquareSize(void) const
{
  return m_squareSize;
}


int Backend::getSquareSpacing(void) const
{
  return m_squareSpacing;
}


void Backend::changeGameState(GameState_ns::GameState gameState)
{
  m_gameState = gameState;
  emit gameStateChanged();
}


GameState_ns::GameState Backend::getGameState(void)
{
  return m_gameState;
}


void Backend::backgroundInteracted(int mouseX, int mouseY)
{
  m_gameBoard->toggleCellStatusBecauseOfMouseInteraction(mouseX, mouseY);
  emit boardRecalculated();
}


void Backend::backgroundReleased(void)
{
  m_gameBoard->clearHasJustBeenToggledFlag();
}
