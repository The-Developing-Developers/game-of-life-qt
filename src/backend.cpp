#include <QDebug>
#include "backend.h"

Backend::Backend(QObject *parent)
  : QObject{parent}
{;}


Backend::~Backend(void)
{
  delete m_grid;
}


void Backend::initialiseBoard(void)
{
  // qDebug() << __func__ << ": Initialising grid...";
  // qDebug() << __func__ << ":   - Number of rows: " << numOfRows;
  // qDebug() << __func__ << ":   - Number of cols: " << numOfCols;
  m_grid = new GameBoard(m_numOfRows, m_numOfCols);
}


void Backend::clearBoard(void)
{
  m_grid->clearBoard();
  emit boardRecalculated();
}


void Backend::recalculateBoard(void)
{
  m_grid->recalculateBoard();
  emit boardRecalculated();
}


bool Backend::getCellStatus(int cellIndex)
{
  return m_grid->getCellStatus(cellIndex);
}


void Backend::setCellStatus(int cellIndex, bool isAlive)
{
  m_grid->setCellStatus(cellIndex, isAlive);
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