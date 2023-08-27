#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <utility>
#include <qqmlintegration.h>
#include "gameboard.hpp"

class Backend : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int rows         READ getNumOfRows   WRITE setNumOfRows    FINAL)
  Q_PROPERTY(int cols         READ getNumOfCols   WRITE setNumOfCols    FINAL)
  Q_PROPERTY(int timerPeriod  READ getTimerPeriod WRITE setTimerPeriod  FINAL)
  Q_PROPERTY(int squareSize   READ getSquareSize  WRITE setSquareSize   FINAL)
  QML_ELEMENT

public:
  explicit Backend(QObject *parent = nullptr);
          ~Backend(void);

  Q_INVOKABLE void initialiseBoard(void);
  Q_INVOKABLE void clearBoard     (void);
  Q_INVOKABLE int  getNumOfRows   (void) const;
  Q_INVOKABLE int  getNumOfCols   (void) const;
  Q_INVOKABLE int  getTimerPeriod (void) const;
  Q_INVOKABLE int  getSquareSize  (void) const;

public slots:
  void recalculateBoard (void);
  bool getCellStatus    (int cellIndex);
  void setCellStatus    (int index, bool isAlive);
  void setNumOfRows     (int numOfRows);
  void setNumOfCols     (int numOfCols);
  void setTimerPeriod   (int timerPeriod_ms);
  void setSquareSize    (int squareSize);

signals:
  void boardRecalculated(void);

private:
  static constexpr int m_minNumOfRowsAndCols  = 5;
  static constexpr int m_minTimerPeriod_ms    = 50;
  static constexpr int m_minSquareSize        = 10;
  int        m_numOfRows       = 5;
  int        m_numOfCols       = 5;
  int        m_timerPeriod_ms  = 250;
  int        m_squareSize      = 50;
  GameBoard* m_grid;
};

#endif // BACKEND_H
