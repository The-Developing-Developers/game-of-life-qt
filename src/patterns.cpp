#include "patterns.hpp"

Patterns::Patterns(void)
  : m_listOfShapes(QStringList()  << stillLifes
                                  << block
                                  << beeHive
                                  << loaf
                                  << boat
                                  << tub
                                  << oscillators
                                  << blinker
                                  << toad
                                  << beacon
                                  << pulsar
                                  << pentaDecathlon
                                  << spaceships
                                  << glider)
{;}

void Patterns::setShapeIndex(int index)
{
  m_currentIndex = index;
  const QString currentShape(m_listOfShapes[m_currentIndex]);

  QVector<QVector<bool>> newMatrix;

  if (currentShape == stillLifes || currentShape == oscillators || currentShape == spaceships)
  {
    return; // do nothing
  }
  if (currentShape == block)
  {
    m_shapeRows = 4;
    m_shapeCols = 4;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0});
  }
  else if (currentShape == beeHive)
  {
    m_shapeRows = 5;
    m_shapeCols = 6;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 0, 0, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
  }
  else if (currentShape == loaf)
  {
    m_shapeRows = 6;
    m_shapeCols = 6;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 0, 0, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
  }
  else if (currentShape == boat)
  {
    m_shapeRows = 5;
    m_shapeCols = 5;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 0, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
  }
  else if (currentShape == tub)
  {
    m_shapeRows = 5;
    m_shapeCols = 5;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 0, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
  }
  else if (currentShape == toad)
  {
    m_shapeRows = 6;
    m_shapeCols = 6;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
  }
  else if (currentShape == blinker)
  {
    m_shapeRows = 5;
    m_shapeCols = 5;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
  }
  else if (currentShape == beacon)
  {
    m_shapeRows = 6;
    m_shapeCols = 6;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
  }
  else if (currentShape == pulsar)
  {
    m_shapeRows = 17;
    m_shapeCols = 17;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
  }
  else if (currentShape == pentaDecathlon)
  {
    m_shapeRows = 18;
    m_shapeCols = 11;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
  }
  else if (currentShape == glider)
  {
    m_shapeRows = 20;
    m_shapeCols = 20;
    newMatrix.push_back(QVector<bool>{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
  }
  else
  {
    m_shapeRows = 3;
    m_shapeCols = 3;
    newMatrix.push_back(QVector<bool>{0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0});
  }

  m_shapeMatrix = newMatrix;
}

const QStringList Patterns::getListOfShapes(void) const
{
  return m_listOfShapes;
}

int Patterns::getCurrentShapeNumOfRows(void) const
{
  return m_shapeRows;
}

int Patterns::getCurrentShapeNumOfCols(void) const
{
  return m_shapeCols;
}

const QVector<QVector<bool>> Patterns::getCurrentShapeMatrix(void) const
{
  return m_shapeMatrix;
}
