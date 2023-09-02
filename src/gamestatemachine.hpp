#ifndef GAMESTATEMACHINE_HPP
#define GAMESTATEMACHINE_HPP

#include <QObject>

namespace GameState_ns
{
  Q_NAMESPACE // required for meta object creation

  enum class GameState_e
  {
    Undefined = 0,
    WelcomeScreen,
    GameBoard,

    HowMany
  };

  Q_ENUM_NS(GameState_e) // register the enum in meta object data
}

class GameStateMachine
{
public:

  enum class RequiredAction
  {
    noAction = 0,
    reinitialiseGameBoard,
    undefined,

    howMany
  };

   GameStateMachine(void);
  ~GameStateMachine(void);

  RequiredAction            requestGameStateChangeAndReceiveFeedback(GameState_ns::GameState_e requestedGameState);
  GameState_ns::GameState_e getGameState    (void) const;

private:

  GameState_ns::GameState_e m_currentGameState = GameState_ns::GameState_e::Undefined;
};

#endif // GAMESTATEMACHINE_HPP
