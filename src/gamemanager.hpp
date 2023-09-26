#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <qqmlintegration.h>
#include "gameboard.hpp"
#include "gameoptions.hpp"
#include "gamestatemachine.hpp"

class GameManager : public QObject
{
  Q_OBJECT
  QML_ELEMENT

public:

  explicit GameManager(QObject *parent = nullptr);
          ~GameManager(void);

  Q_INVOKABLE void clearBoard           (void);
  Q_INVOKABLE void recalculateBoard     (void);
  Q_INVOKABLE int  getNumOfRows         (void) const;
  Q_INVOKABLE int  getNumOfCols         (void) const;
  Q_INVOKABLE int  getTimerPeriod       (void) const;
  Q_INVOKABLE int  getSquareSize        (void) const;
  Q_INVOKABLE int  getSquareSpacing     (void) const;
  Q_INVOKABLE bool isGameTimerRunning   (void) const;
  Q_INVOKABLE bool getCellStatus        (int cellIndex);
  Q_INVOKABLE void setNumOfRows         (int numOfRows);
  Q_INVOKABLE void setNumOfCols         (int numOfCols);
  Q_INVOKABLE void setTimerPeriod       (int timerPeriod_ms);
  Q_INVOKABLE void setSquareSize        (int squareSize);
  Q_INVOKABLE void setSquareSpacing     (int squareSpacing);
  Q_INVOKABLE void setGameTimerStatus   (bool);
  Q_INVOKABLE void backgroundInteracted (int mouseX, int mouseY);
  Q_INVOKABLE void backgroundReleased   (void);
  Q_INVOKABLE void changeGameState      (GameState_ns::GameState_e gameState);
  Q_INVOKABLE GameState_ns::GameState_e getGameState(void) const;

  bool          doesBoardNeedResizing (void) const;
  void          stopTheTimer          (void);
  GameOptions&  getGameOptions        (void) const;

signals:

  void boardChanged(void);
  void gameStateChanged (GameState_ns::GameState_e currentState);
  void stopTimer(void);

private:

  QScopedPointer<GameOptions>      m_gameOptions;
  QScopedPointer<GameBoard>        m_gameBoard;
  QScopedPointer<GameStateMachine> m_gameStateMachine;
  bool                             m_isGameTimerRunning;

  void resizeGameBoard(void);
};

#endif // GAMEMANAGER_H
