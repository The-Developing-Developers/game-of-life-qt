#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
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

  Q_INVOKABLE void initialiseBoard(int numOfRows, int numOfCols);
  Q_INVOKABLE void clearBoard     (void);

public slots:
  void recalculateBoard(void);
  bool getCellStatus(int cellIndex);
  void setCellStatus(int index, bool isAlive);

signals:
  void boardRecalculated(void);

private:
  Grid* m_grid;
};

#endif // BACKEND_H
