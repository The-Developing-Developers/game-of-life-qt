#include "gameoptions.hpp"

GameOptions::GameOptions(void)
{;}


GameOptions::~GameOptions(void)
{;}


void GameOptions::setNumOfRows(int numOfRows)
{
  if (numOfRows >= m_minNumOfRowsAndCols)
    m_numOfRows = numOfRows;
  else
    m_numOfRows = m_minNumOfRowsAndCols;
}


void GameOptions::setNumOfCols(int numOfCols)
{
  if (numOfCols >= m_minNumOfRowsAndCols)
    m_numOfCols = numOfCols;
  else
    m_numOfCols = m_minNumOfRowsAndCols;
}


void GameOptions::setTimerPeriod(int timerPeriod_ms)
{
  if (timerPeriod_ms >= m_minTimerPeriod_ms)
    m_timerPeriod_ms = timerPeriod_ms;
  else
    m_timerPeriod_ms = m_minTimerPeriod_ms;
}


void GameOptions::setSquareSize(int squareSize)
{
  if (squareSize >= m_minSquareSize)
    m_squareSize = squareSize;
  else
    m_squareSize = m_minSquareSize;
}


void GameOptions::setSquareSpacing(int squareSpacing)
{
  if (squareSpacing >= m_minSquareSpacing)
    m_squareSpacing = squareSpacing;
  else
    m_squareSpacing = m_minSquareSpacing;
}


int GameOptions::getNumOfRows(void) const
{
  return m_numOfRows;
}


int GameOptions::getNumOfCols(void) const
{
  return m_numOfCols;
}


int GameOptions::getNumOfRows_initial(void)
{
  int numOfRows_initial = m_numOfRows_initial;
  updateNumOfRows();
  return numOfRows_initial;
}


int GameOptions::getTimerPeriod(void) const
{
  return m_timerPeriod_ms;
}


int GameOptions::getSquareSize(void) const
{
  return m_squareSize;
}


int GameOptions::getSquareSpacing(void) const
{
  return m_squareSpacing;
}


int GameOptions::getDeadOrAliveLowerThreshold(void) const
{
  return m_DeadOrAliveLowerThreshold;
}


int GameOptions::getDeadOrAliveUpperThreshold(void) const
{
  return m_DeadOrAliveUpperThreshold;
}


void GameOptions::updateNumOfRows(void)
{
  m_numOfRows_initial = m_numOfRows;
}