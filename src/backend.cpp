#include <QDebug>
#include "backend.h"

Backend::Backend(QObject *parent)
  : QObject{parent}
{;}


Backend::~Backend(void)
{
  delete m_grid;
}


void Backend::initialiseGrid(int numOfRows, int numOfCols)
{
  qDebug() << __func__ << ": Initialising grid...";
  qDebug() << __func__ << ":   - Number of rows: " << numOfRows;
  qDebug() << __func__ << ":   - Number of cols: " << numOfCols;
  m_grid = new Grid(numOfRows, numOfCols);
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


void Backend::setCellStatus(int index, bool isAlive)
{
  m_grid->setCellStatus(index, isAlive);
}