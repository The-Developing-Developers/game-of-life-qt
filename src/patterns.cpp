#include "patterns.hpp"

Patterns::Patterns(QObject *parent)
  : QAbstractListModel(parent)
  , m_listOfPatterns(QStringList()  << stillLifes
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


/**
 * @brief This method is used by views and delegates to know how many items they need to show.
 *
 * @param parent
 * @return `int` the number of items in the model.
 **/
int Patterns::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0; // In a list model, it should always return 0. Other more complex data models, such as trees, may return a non-zero value for a valid parent.

  return m_listOfPatterns.size();
}


/**
 * @brief This method is used to provide data from the model to a view.
 *
 * @param index a `QModelIndex` that specifies the item in the model.
 * @param role an `int` that specifies the role of the data.
 * @return the data for the item at this position in the list, wrapped in a `QVariant`. Wrapping the data in a `QVariant` allows it to handle many different data types.
 **/
QVariant Patterns::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (role == NameRole)
    return QVariant(m_listOfPatterns[index.row()]);

  return QVariant();
}


/**
 * @brief In QML, it's more convenient to access data roles by name rather than by integer.
 *
 * @return `QHash<int, QByteArray>` that maps each role's integer identifier to its name.
 **/
QHash<int, QByteArray> Patterns::roleNames() const
{
  QHash<int, QByteArray> names; // Similar to 'std::map'?
  names[NameRole] = "name";
  return names;
}


/**
 * @brief TODO: the name of this method is poorly chosen, because it also generates the new pattern matrix that will be read by the
 * 'GameManager' with the 'getCurrentPatternMatrix' method. Consider changing the name, and even refactoring the whole function, maybe by
 * splitting it into smaller functions.
 *
 * @param index Index of the shape pattern chosen by the user in the QML front-end.
 **/
void Patterns::setPatternIndex(int index)
{
  m_currentIndex = index; // TODO: is this assignation necessary? Can't `index` be used instead in the following line of code?
  const QString currentPattern(m_listOfPatterns[m_currentIndex]);

  QVector<QVector<bool>> newMatrix;

  if (currentPattern == stillLifes || currentPattern == oscillators || currentPattern == spaceships)
  {
    return; // do nothing: they are just list separators, not patterns
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


// // TODO: unused
// const QStringList Patterns::getListOfPatterns(void) const
// {
//   return m_listOfPatterns;
// }


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
