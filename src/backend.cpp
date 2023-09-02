#include <QDebug>
#include "backend.h"

Backend::Backend(QObject *parent)
  : QObject{parent},
    m_gameOptions     (new GameOptions),
    m_gameBoard       (new GameBoard(m_gameOptions)),
    m_gameStateMachine(new GameStateMachine)
{;}


Backend::~Backend(void)
{
  if (m_gameStateMachine != nullptr)
    delete m_gameStateMachine;

  if (m_gameBoard != nullptr)
    delete m_gameBoard;

  if (m_gameOptions != nullptr)
    delete m_gameOptions;
}


void Backend::reInitialiseBoard(void)
{
  if (m_gameBoard != nullptr)
    delete m_gameBoard;

  m_gameBoard = new GameBoard(m_gameOptions);
}


void Backend::clearBoard(void)
{
  m_gameBoard->clearBoard();
  emit boardRecalculated();
}


void Backend::recalculateBoard(void)
{
  m_gameBoard->recalculateBoard();
  emit boardRecalculated();
}


bool Backend::getCellStatus(int cellIndex)
{
  return m_gameBoard->getCellStatus(cellIndex);
}


void Backend::setNumOfRows(int numOfRows)
{
  m_gameOptions->setNumOfRows(numOfRows);
}


void Backend::setNumOfCols(int numOfCols)
{
  m_gameOptions->setNumOfCols(numOfCols);
}


void Backend::setTimerPeriod(int timerPeriod_ms)
{
  m_gameOptions->setTimerPeriod(timerPeriod_ms);
}


void Backend::setSquareSize(int squareSize)
{
  m_gameOptions->setSquareSize(squareSize);
}


void Backend::setSquareSpacing(int squareSpacing)
{
  m_gameOptions->setSquareSpacing(squareSpacing);
}


int Backend::getNumOfRows(void) const
{
  return m_gameOptions->getNumOfRows();
}


int Backend::getNumOfCols(void) const
{
  return m_gameOptions->getNumOfCols();
}


int Backend::getTimerPeriod(void) const
{
  return m_gameOptions->getTimerPeriod();
}


int Backend::getSquareSize(void) const
{
  return m_gameOptions->getSquareSize();
}


int Backend::getSquareSpacing(void) const
{
  return m_gameOptions->getSquareSpacing();
}


void Backend::changeGameState(GameState_ns::GameState_e gameState)
{
  GameStateMachine::RequiredAction requiredAction = m_gameStateMachine->requestGameStateChangeAndReceiveFeedback(gameState);

  switch (requiredAction)
  {
    case GameStateMachine::RequiredAction::noAction:
      break;

    case GameStateMachine::RequiredAction::reinitialiseGameBoard:
      reInitialiseBoard();
      break;

    case GameStateMachine::RequiredAction::undefined:
    default:
      qDebug() << "Error during state change";
      break;
  }

  emit gameStateChanged(m_gameStateMachine->getGameState());
}


GameState_ns::GameState_e Backend::getGameState(void)
{
  return m_gameStateMachine->getGameState();
}


void Backend::backgroundInteracted(int mouseX, int mouseY)
{
  m_gameBoard->toggleCellStatusBecauseOfMouseInteraction(mouseX, mouseY);
  emit boardRecalculated();
}


void Backend::backgroundReleased(void)
{
  m_gameBoard->clearHasJustBeenToggledFlag();
}