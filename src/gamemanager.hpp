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

  Q_PROPERTY(bool isAnimationAllowed READ getIsAnimationAllowed WRITE setIsAnimationAllowed NOTIFY isAnimationAllowedChanged)
  Q_PROPERTY(int numOfRows READ getNumOfRows WRITE setNumOfRows NOTIFY numOfRowsChanged)
  Q_PROPERTY(int numOfCols READ getNumOfCols WRITE setNumOfCols NOTIFY numOfColsChanged)

  Q_INVOKABLE void clearBoard           (void);
  Q_INVOKABLE void recalculateBoard     (void);
  Q_INVOKABLE int  getNumOfRows         (void) const;
  Q_INVOKABLE int  getNumOfCols         (void) const;
  Q_INVOKABLE int  getTimerPeriod       (void) const;
  Q_INVOKABLE int  getSquareSize        (void) const;
  Q_INVOKABLE int  getSquareSpacing     (void) const;
  Q_INVOKABLE bool getIsAnimationAllowed(void);
  Q_INVOKABLE bool getCellStatus        (int cellIndex);
  Q_INVOKABLE void setNumOfRows         (int numOfRows);
  Q_INVOKABLE void setNumOfCols         (int numOfCols);
  Q_INVOKABLE void setTimerPeriod       (int timerPeriod_ms);
  Q_INVOKABLE void setSquareSize        (int squareSize);
  Q_INVOKABLE void setSquareSpacing     (int squareSpacing);
  Q_INVOKABLE void setIsAnimationAllowed(bool isAnimationAllowed);
  Q_INVOKABLE void backgroundInteracted (int mouseX, int mouseY);
  Q_INVOKABLE void backgroundReleased   (void);
  // Q_INVOKABLE void changeGameState      (GameState_ns::GameState_e gameState); // Currently not used
  Q_INVOKABLE GameState_ns::GameState_e getGameState(void) const;

  bool          doesBoardNeedResizing (void) const;
  void          stopTheTimer          (void);
  GameOptions&  getGameOptions        (void) const;

signals:

  void boardChanged(void);
  void gameStateChanged (GameState_ns::GameState_e currentState);
  void stopTimer(void);
  void isAnimationAllowedChanged(void);
  void numOfRowsChanged(int);
  void numOfColsChanged(int);

private:

  QScopedPointer<GameOptions>      m_gameOptions;
  QScopedPointer<GameBoard>        m_gameBoard;
  QScopedPointer<GameStateMachine> m_gameStateMachine;
  bool m_isAnimationAllowed;

  void resizeGameBoard(void);
};

#endif // GAMEMANAGER_H
