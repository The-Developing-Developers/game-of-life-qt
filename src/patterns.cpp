#include "patterns.hpp"

Patterns::Patterns(void)
  : m_listOfPatterns(QStringList()  << stillLifes
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

// TODO: the name of this method is poorly chosen.
void Patterns::setPatternIndex(int index)
{
  m_currentIndex = index;
  const QString currentPattern(m_listOfPatterns[m_currentIndex]);

  QVector<QVector<bool>> newMatrix;

  if (currentPattern == stillLifes || currentPattern == oscillators || currentPattern == spaceships)
  {
    return; // do nothing
  }
  if (currentPattern == block)
  {
    m_patternRows = 4;
    m_patternCols = 4;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0});
  }
  else if (currentPattern == beeHive)
  {
    m_patternRows = 5;
    m_patternCols = 6;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 0, 0, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
  }
  else if (currentPattern == loaf)
  {
    m_patternRows = 6;
    m_patternCols = 6;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 0, 0, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
  }
  else if (currentPattern == boat)
  {
    m_patternRows = 5;
    m_patternCols = 5;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 0, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
  }
  else if (currentPattern == tub)
  {
    m_patternRows = 5;
    m_patternCols = 5;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 0, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
  }
  else if (currentPattern == toad)
  {
    m_patternRows = 6;
    m_patternCols = 6;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 1, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 1, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
  }
  else if (currentPattern == blinker)
  {
    m_patternRows = 5;
    m_patternCols = 5;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0});
  }
  else if (currentPattern == beacon)
  {
    m_patternRows = 6;
    m_patternCols = 6;
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 1, 1, 0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 1, 1, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0, 0, 0, 0});
  }
  else if (currentPattern == pulsar)
  {
    m_patternRows = 17;
    m_patternCols = 17;
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
  else if (currentPattern == pentaDecathlon)
  {
    m_patternRows = 18;
    m_patternCols = 11;
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
  else if (currentPattern == glider)
  {
    m_patternRows = 20;
    m_patternCols = 20;
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
    m_patternRows = 3;
    m_patternCols = 3;
    newMatrix.push_back(QVector<bool>{0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0});
    newMatrix.push_back(QVector<bool>{0, 0, 0});
  }

  m_patternMatrix = newMatrix;
}

const QStringList Patterns::getListOfPatterns(void) const
{
  return m_listOfPatterns;
}

int Patterns::getCurrentPatternNumOfRows(void) const
{
  return m_patternRows;
}

int Patterns::getCurrentPatternNumOfCols(void) const
{
  return m_patternCols;
}

const QVector<QVector<bool>> Patterns::getCurrentPatternMatrix(void) const
{
  return m_patternMatrix;
}
