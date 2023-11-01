#include "gameoptions.hpp"

GameOptions::GameOptions(void)
{;}


GameOptions::~GameOptions(void)
{;}


void GameOptions::setNumOfRows(int numOfRows)
{
  if (numOfRows > m_maxNumOfRowsAndCols)
    m_numOfRows = m_maxNumOfRowsAndCols;
  else
  {
    if (numOfRows < m_minNumOfRowsAndCols)
      m_numOfRows = m_minNumOfRowsAndCols;
    else
      m_numOfRows = numOfRows;
  }
}


void GameOptions::setNumOfCols(int numOfCols)
{
  if (numOfCols > m_maxNumOfRowsAndCols)
    m_numOfCols = m_maxNumOfRowsAndCols;
  else
  {
    if (numOfCols < m_minNumOfRowsAndCols)
      m_numOfCols = m_minNumOfRowsAndCols;
    else
      m_numOfCols = numOfCols;
  }
}


void GameOptions::setTimerPeriod(int timerPeriod_ms)
{
  if (timerPeriod_ms > m_maxTimerPeriod_ms)
    m_timerPeriod_ms = m_maxTimerPeriod_ms;
  else
  {
    if (timerPeriod_ms < m_minTimerPeriod_ms)
      m_timerPeriod_ms = m_minTimerPeriod_ms;
    else
      m_timerPeriod_ms = timerPeriod_ms;
  }
}


void GameOptions::setSquareSize(int squareSize)
{
  if (squareSize > m_maxSquareSize)
    m_squareSize = m_maxSquareSize;
  else
  {
    if (squareSize < m_minSquareSize)
      m_squareSize = m_minSquareSize;
    else
      m_squareSize = squareSize;
  }
}


void GameOptions::setSquareSpacing(int squareSpacing)
{
  if (squareSpacing > m_maxSquareSpacing)
    m_squareSpacing = m_maxSquareSpacing;
  else
  {
    if (squareSpacing < m_minSquareSpacing)
      m_squareSpacing = m_minSquareSpacing;
    else
      m_squareSpacing = squareSpacing;
  }
}


int GameOptions::getNumOfRows(void) const
{
  return m_numOfRows;
}


int GameOptions::getNumOfCols(void) const
{
  return m_numOfCols;
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


int GameOptions::getMinNumOfRowsAndCols(void) const
{
  return m_minNumOfRowsAndCols;
}


int GameOptions::getMaxNumOfRowsAndCols(void) const
{
  return m_maxNumOfRowsAndCols;
}


int GameOptions::getMinTimerPeriod_ms(void) const
{
  return m_minTimerPeriod_ms;
}


int GameOptions::getMaxTimerPeriod_ms(void) const
{
  return m_maxTimerPeriod_ms;
}


int GameOptions::getMinSquareSize(void) const
{
  return m_minSquareSize;
}


int GameOptions::getMaxSquareSize(void) const
{
  return m_maxSquareSize;
}


int GameOptions::getMinSquareSpacing(void) const
{
  return m_minSquareSpacing;
}


int GameOptions::getMaxSquareSpacing(void) const
{
  return m_maxSquareSpacing;
}