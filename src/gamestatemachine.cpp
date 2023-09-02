#include <QQmlEngine>
#include "gamestatemachine.hpp"

GameStateMachine::GameStateMachine(void)
{
  qmlRegisterUncreatableMetaObject
  (
    GameState_ns::staticMetaObject, // meta object created by Q_NAMESPACE macro
    "GameStateEnum",                // import statement (can be any string)
    1, 0,                           // major and minor version of the import
    "GameState",                    // name to be used in QML (does not have to match C++ name)
    "Error: only enums"             // error in case someone tries to create a namespace object
  );
}


GameStateMachine::~GameStateMachine(void)
{;}


bool GameStateMachine::changeGameStateAndReinitIfNecessary(GameState_ns::GameState_e requestedGameState)
{
  bool isItNecessaryToReinitTheBoard = false;

  if (requestedGameState == GameState_ns::GameState_e::GameBoard)
    isItNecessaryToReinitTheBoard = true;

  m_currentGameState = requestedGameState;

  return isItNecessaryToReinitTheBoard;
}


GameState_ns::GameState_e GameStateMachine::getGameState(void) const
{
  return m_currentGameState;
}