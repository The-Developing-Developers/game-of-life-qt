#include <QQmlEngine>
#include "gamestatemachine.hpp"
#include "gamemanager.hpp"

GameStateMachine::GameStateMachine(GameManager& backend)
  : m_gameManager(backend)
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


GameStateMachine::RequiredAction GameStateMachine::requestGameStateChangeAndReceiveFeedback(GameState_ns::GameState_e requestedGameState)
{
  RequiredAction requiredAction = RequiredAction::noAction;

  if (    requestedGameState == GameState_ns::GameState_e::GameBoard
      &&  m_gameManager.doesBoardNeedResizing() )
    requiredAction = RequiredAction::resizeGameBoard;

  m_currentGameState = requestedGameState;

  return requiredAction;
}


GameState_ns::GameState_e GameStateMachine::getGameState(void) const
{
  return m_currentGameState;
}