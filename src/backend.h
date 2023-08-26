#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
// #include <QDebug> // TODO: togliere dopo test di rowcol
#include <utility>
#include <qqmlintegration.h>
#include "grid.hpp"

class Backend : public QObject
{
  Q_OBJECT
  QML_ELEMENT

public:
  explicit Backend(QObject *parent = nullptr);
          ~Backend(void);

  Q_INVOKABLE void initialiseGrid(int numOfRows, int numOfCols);
  // Q_INVOKABLE int setGridRows(int numOfRows);
  // Q_INVOKABLE int setGridCols(int numOfCols);

public slots:
  void recalculateBoard(void);
  bool getCellStatus(int cellIndex);
  void setCellStatus(int index, bool isAlive);

  // TODO: debug
  // void testRowColFromIndex(int index)
  // {
  //   std::pair<int, int> numbers = m_grid->rowColFromIndex(index);
  //   qDebug() << "Index: " << index;
  //   qDebug() << "  - Row: " << numbers.first;
  //   qDebug() << "  - Col: " << numbers.second;
  // }

signals:
  void boardRecalculated(void);

private:
  Grid* m_grid;
};

#endif // BACKEND_H
