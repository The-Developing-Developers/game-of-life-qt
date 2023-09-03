#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqmlintegration.h>
#include <memory>
#include "gameboard.hpp"
#include "gameoptions.hpp"
#include "gamestatemachine.hpp"

class Backend : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int rows           READ getNumOfRows     WRITE setNumOfRows      FINAL)
  Q_PROPERTY(int cols           READ getNumOfCols     WRITE setNumOfCols      FINAL)
  Q_PROPERTY(int timerPeriod    READ getTimerPeriod   WRITE setTimerPeriod    FINAL)
  Q_PROPERTY(int squareSize     READ getSquareSize    WRITE setSquareSize     FINAL)
  Q_PROPERTY(int squareSpacing  READ getSquareSpacing WRITE setSquareSpacing  FINAL)
  QML_ELEMENT

public:
  explicit Backend(QObject *parent = nullptr);
          ~Backend(void);

  Q_INVOKABLE void reInitialiseBoard  (void);
  Q_INVOKABLE void clearBoard       (void);
  Q_INVOKABLE int  getNumOfRows     (void) const;
  Q_INVOKABLE int  getNumOfCols     (void) const;
  Q_INVOKABLE int  getTimerPeriod   (void) const;
  Q_INVOKABLE int  getSquareSize    (void) const;
  Q_INVOKABLE int  getSquareSpacing (void) const;
  Q_INVOKABLE void changeGameState  (GameState_ns::GameState_e gameState);

public slots:
  void recalculateBoard     (void);
  bool getCellStatus        (int cellIndex);
  void setNumOfRows         (int numOfRows);
  void setNumOfCols         (int numOfCols);
  void setTimerPeriod       (int timerPeriod_ms);
  void setSquareSize        (int squareSize);
  void setSquareSpacing     (int squareSpacing);
  void backgroundInteracted (int mouseX, int mouseY);
  void backgroundReleased   (void);
  GameState_ns::GameState_e getGameState(void);

signals:
  void boardRecalculated(void);
  void gameStateChanged (GameState_ns::GameState_e currentState);

private:
  std::unique_ptr<GameOptions>      m_gameOptions;
  std::unique_ptr<GameBoard>        m_gameBoard;
  std::unique_ptr<GameStateMachine> m_gameStateMachine;
};

#endif // BACKEND_H
