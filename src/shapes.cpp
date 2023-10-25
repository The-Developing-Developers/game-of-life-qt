#include "shapes.hpp"

Shapes::Shapes(void)
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

void Shapes::setShapeIndex(int index)
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
    newMatrix.push_back(QVector<bool>{false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, true,  true,  false});
    newMatrix.push_back(QVector<bool>{false, true,  true,  false});
    newMatrix.push_back(QVector<bool>{false, false, false, false});
  }
  else if (currentShape == beeHive)
  {
    m_shapeRows = 5;
    m_shapeCols = 6;
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, true,  true,  false, false});
    newMatrix.push_back(QVector<bool>{false, true, false, false,  true,  false});
    newMatrix.push_back(QVector<bool>{false, false, true,  true,  false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false});
  }
  else if (currentShape == loaf)
  {
    m_shapeRows = 6;
    m_shapeCols = 6;
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, false, true,   true,   false,  false});
    newMatrix.push_back(QVector<bool>{false, true,  false,  false,  true,   false});
    newMatrix.push_back(QVector<bool>{false, false, true,   false,  true,   false});
    newMatrix.push_back(QVector<bool>{false, false, false,  true,   false,  false});
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false,  false});
  }
  else if (currentShape == boat)
  {
    m_shapeRows = 5;
    m_shapeCols = 5;
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, true,  true,   false,  false});
    newMatrix.push_back(QVector<bool>{false, true,  false,  true,   false});
    newMatrix.push_back(QVector<bool>{false, false, true,   false,  false});
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false});
  }
  else if (currentShape == tub)
  {
    m_shapeRows = 5;
    m_shapeCols = 5;
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, false, true,   false,  false});
    newMatrix.push_back(QVector<bool>{false, true,  false,  true,   false});
    newMatrix.push_back(QVector<bool>{false, false, true,   false,  false});
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false});
  }
  else if (currentShape == toad)
  {
    m_shapeRows = 6;
    m_shapeCols = 6;
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, false, true,   true,   true,   false});
    newMatrix.push_back(QVector<bool>{false, true,  true,   true,   false,  false});
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false,  false});
  }
  else if (currentShape == blinker)
  {
    m_shapeRows = 5;
    m_shapeCols = 5;
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, true,  true,   true,   false});
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false});
  }
  else if (currentShape == beacon)
  {
    m_shapeRows = 6;
    m_shapeCols = 6;
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, true,  true,   false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, true,  true,   false,  false,  false});
    newMatrix.push_back(QVector<bool>{false, false, false,  true,   true,   false});
    newMatrix.push_back(QVector<bool>{false, false, false,  true,   true,   false});
    newMatrix.push_back(QVector<bool>{false, false, false,  false,  false,  false});
  }
  else if (currentShape == pulsar)
  {
    m_shapeRows = 17;
    m_shapeCols = 17;
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, true,  true,  true,  false, false, false, true,  true,  true,  false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, true,  false, false, false, false, true,  false, true,  false, false, false, false, true,  false, false});
    newMatrix.push_back(QVector<bool>{false, false, true,  false, false, false, false, true,  false, true,  false, false, false, false, true,  false, false});
    newMatrix.push_back(QVector<bool>{false, false, true,  false, false, false, false, true,  false, true,  false, false, false, false, true,  false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, true,  true,  true,  false, false, false, true,  true,  true,  false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, true,  true,  true,  false, false, false, true,  true,  true,  false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, true,  false, false, false, false, true,  false, true,  false, false, false, false, true,  false, false});
    newMatrix.push_back(QVector<bool>{false, false, true,  false, false, false, false, true,  false, true,  false, false, false, false, true,  false, false});
    newMatrix.push_back(QVector<bool>{false, false, true,  false, false, false, false, true,  false, true,  false, false, false, false, true,  false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, true,  true,  true,  false, false, false, true,  true,  true,  false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
  }
  else if (currentShape == pentaDecathlon)
  {
    m_shapeRows = 18;
    m_shapeCols = 11;
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, true,  false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, true,  false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, true,  false, true,  false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, true,  false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, true,  false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, true,  false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, true,  false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, true,  false, true,  false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, true,  false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, true,  false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false});
  }
  else if (currentShape == glider)
  {
    m_shapeRows = 20;
    m_shapeCols = 20;
    newMatrix.push_back(QVector<bool>{false, true,  false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, true,  false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{true,  true,  true,  false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false});
  }
  else
  {
    m_shapeRows = 3;
    m_shapeCols = 3;
    newMatrix.push_back(QVector<bool>{false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false});
    newMatrix.push_back(QVector<bool>{false, false, false});
  }

  m_shapeMatrix = newMatrix;
}

const QStringList Shapes::getListOfShapes(void) const
{
  return m_listOfShapes;
}

int Shapes::getCurrentShapeNumOfRows(void) const
{
  return m_shapeRows;
}

int Shapes::getCurrentShapeNumOfCols(void) const
{
  return m_shapeCols;
}

const QVector<QVector<bool>> Shapes::getCurrentShapeMatrix(void) const
{
  return m_shapeMatrix;
}
