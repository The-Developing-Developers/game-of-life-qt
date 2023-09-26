#include <QDebug>
#include "gamemanager.hpp"

GameManager::GameManager(QObject *parent)
  : QObject           (parent)
  , m_gameOptions     (new GameOptions)
  , m_gameBoard       (new GameBoard(*this))
  , m_gameStateMachine(new GameStateMachine(*this))
{;}


GameManager::~GameManager(void)
{;}


void GameManager::resizeGameBoard(void)
{
  m_gameBoard->resizeGameBoard();
}


void GameManager::clearBoard(void)
{
  m_gameBoard->clearBoard();
  emit boardChanged();
}


void GameManager::recalculateBoard(void)
{
  m_gameBoard->recalculateBoard();
  emit boardChanged();
}


bool GameManager::getCellStatus(int cellIndex)
{
  return m_gameBoard->getCellStatus(cellIndex);
}


void GameManager::setNumOfRows(int numOfRows)
{
  m_gameOptions->setNumOfRows(numOfRows);
  m_gameBoard->flagBoardForResizing();
}


void GameManager::setNumOfCols(int numOfCols)
{
  m_gameOptions->setNumOfCols(numOfCols);
  m_gameBoard->flagBoardForResizing();
}


void GameManager::setTimerPeriod(int timerPeriod_ms)
{
  m_gameOptions->setTimerPeriod(timerPeriod_ms);
}


void GameManager::setSquareSize(int squareSize)
{
  m_gameOptions->setSquareSize(squareSize);
}


void GameManager::setSquareSpacing(int squareSpacing)
{
  m_gameOptions->setSquareSpacing(squareSpacing);
}


int GameManager::getNumOfRows(void) const
{
  return m_gameOptions->getNumOfRows();
}


int GameManager::getNumOfCols(void) const
{
  return m_gameOptions->getNumOfCols();
}


int GameManager::getTimerPeriod(void) const
{
  return m_gameOptions->getTimerPeriod();
}


int GameManager::getSquareSize(void) const
{
  return m_gameOptions->getSquareSize();
}


int GameManager::getSquareSpacing(void) const
{
  return m_gameOptions->getSquareSpacing();
}


void GameManager::changeGameState(GameState_ns::GameState_e gameState)
{
  GameStateMachine::RequiredAction requiredAction = m_gameStateMachine->requestGameStateChangeAndReceiveFeedback(gameState);

  switch (requiredAction)
  {
    case GameStateMachine::RequiredAction::noAction:
      break;

    case GameStateMachine::RequiredAction::resizeGameBoard:
      resizeGameBoard();
      break;

    case GameStateMachine::RequiredAction::undefined:
    default:
      qDebug() << "Error during state change";
      break;
  }

  emit gameStateChanged(m_gameStateMachine->getGameState());
}


GameState_ns::GameState_e GameManager::getGameState(void) const
{
  return m_gameStateMachine->getGameState();
}


void GameManager::backgroundInteracted(int mouseX, int mouseY)
{
  m_gameBoard->toggleCellStatusBecauseOfMouseInteraction(mouseX, mouseY);
  emit boardChanged();
}


void GameManager::backgroundReleased(void)
{
  m_gameBoard->unlockToggling();
}


bool GameManager::doesBoardNeedResizing(void) const
{
  return m_gameBoard->doesBoardNeedResizing();
}


GameOptions& GameManager::getGameOptions(void) const
{
  return *m_gameOptions;
}


void GameManager::stopTheTimer(void)
{
  emit stopTimer();
}