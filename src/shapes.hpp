#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <QStringList>

class Shapes
{
public:
  Shapes(void);

  void                          setShapeIndex           (int index);
  const QStringList             getListOfShapes         (void) const;
  int                           getCurrentShapeNumOfRows(void) const;
  int                           getCurrentShapeNumOfCols(void) const;
  const QVector<QVector<bool>>  getCurrentShapeMatrix   (void) const;

private:

  const QString stillLifes      = "--- Still Lifes ---";
  const QString block           = "Block";
  const QString beeHive         = "Bee-Hive";
  const QString loaf            = "Loaf";
  const QString boat            = "Boat";
  const QString tub             = "Tub";
  const QString oscillators     = "--- Oscillators ---";
  const QString blinker         = "Blinker";
  const QString toad            = "Toad";
  const QString beacon          = "Beacon";
  const QString pulsar          = "Pulsar";
  const QString pentaDecathlon  = "Penta-Decathlon";
  const QString spaceships      = "--- Spaceships ---";
  const QString glider          = "Glider";

  const QStringList m_listOfShapes;
  QVector<QVector<bool>> m_shapeMatrix;
  int m_currentIndex;
  int m_shapeRows;
  int m_shapeCols;
};

#endif // SHAPES_HPP