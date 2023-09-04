#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqmlintegration.h>
#include "gameboard.hpp"
#include "gameoptions.hpp"
#include "gamestatemachine.hpp"

class Backend : public QObject
{
  Q_OBJECT
  QML_ELEMENT

public:

  explicit Backend(QObject *parent = nullptr);
          ~Backend(void);

  Q_INVOKABLE void clearBoard           (void);
  Q_INVOKABLE int  getNumOfRows         (void) const;
  Q_INVOKABLE int  getNumOfCols         (void) const;
  Q_INVOKABLE int  getTimerPeriod       (void) const;
  Q_INVOKABLE int  getSquareSize        (void) const;
  Q_INVOKABLE int  getSquareSpacing     (void) const;
  Q_INVOKABLE void changeGameState      (GameState_ns::GameState_e gameState);
  Q_INVOKABLE void recalculateBoard     (void);
  Q_INVOKABLE bool getCellStatus        (int cellIndex);
  Q_INVOKABLE void setNumOfRows         (int numOfRows);
  Q_INVOKABLE void setNumOfCols         (int numOfCols);
  Q_INVOKABLE void setTimerPeriod       (int timerPeriod_ms);
  Q_INVOKABLE void setSquareSize        (int squareSize);
  Q_INVOKABLE void setSquareSpacing     (int squareSpacing);
  Q_INVOKABLE void backgroundInteracted (int mouseX, int mouseY);
  Q_INVOKABLE void backgroundReleased   (void);
  Q_INVOKABLE GameState_ns::GameState_e getGameState(void);

  bool          doesBoardNeedResizing (void) const;
  void          stopTheTimer          (void) const;
  GameOptions&  getGameOptions        (void) const;

signals:

  void boardRecalculated(void);
  void gameStateChanged (GameState_ns::GameState_e currentState);
  void stopTimer(void) const;

private:

  QScopedPointer<GameOptions>      m_gameOptions;
  QScopedPointer<GameBoard>        m_gameBoard;
  QScopedPointer<GameStateMachine> m_gameStateMachine;

  void resizeGameBoard(void);
};

#endif // BACKEND_H
