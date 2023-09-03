#include <QDebug>
#include "backend.h"

Backend::Backend(QObject *parent)
  : QObject{parent},
    m_gameOptions     (std::make_unique<GameOptions>()),
    m_gameBoard       (std::make_unique<GameBoard>(*m_gameOptions)),
    m_gameStateMachine(std::make_unique<GameStateMachine>())
{;}


Backend::~Backend(void)
{;}


void Backend::reInitialiseBoard(void)
{
  m_gameBoard.reset();
  m_gameBoard = std::make_unique<GameBoard>(*m_gameOptions);
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