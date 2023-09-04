#include "gameboard.hpp"
#include "gameoptions.hpp"
#include "cell.hpp"
#include "backend.h"

/**
 * @brief Construct a new GameBoard object with custom size.
 **/
GameBoard::GameBoard(GameManager& backend)
  : m_gameManager(backend), m_gameOptions(m_gameManager.getGameOptions())
{
  // Number of rows
  m_currentMatrix.resize(m_gameOptions.getNumOfRows());
  m_nextMatrix.resize(m_gameOptions.getNumOfRows());

  // Number of cols
  for (int i = 0; i != m_gameOptions.getNumOfRows(); ++i)
  {
    m_currentMatrix[i].resize(m_gameOptions.getNumOfCols());
    m_nextMatrix[i].resize(m_gameOptions.getNumOfCols());
  }
}


GameBoard::~GameBoard(void)
{;}


int GameBoard::getIndexFromRowCol(int row, int col)
{
  return row * m_gameOptions.getNumOfCols() + col;
}


std::pair<int, int> GameBoard::getRowColFromIndex(int cellIndex)
{
  int row = 0;
  int col = 0;

  for (int i = 0; i != cellIndex; ++i)
  {
    ++col;

    if (col == m_gameOptions.getNumOfCols())
    {
      ++row;
      col = 0;
    }
  }

  return std::pair<int, int>(row, col);
}


bool GameBoard::getCellStatus(int cellIndex)
{
  std::pair<int, int> rowCol = getRowColFromIndex(cellIndex);
  int row = rowCol.first;
  int col = rowCol.second;
  return m_currentMatrix[row][col].isAlive();
}


void GameBoard::clearBoard(void)
{
  for (int row = 0; row != m_gameOptions.getNumOfRows(); ++row)
  {
    for (int col = 0; col != m_gameOptions.getNumOfCols(); ++col)
    {
      m_currentMatrix[row][col].kill();
      m_nextMatrix [row][col].kill();
    }
  }
}


void GameBoard::recalculateBoard(void)
{
  calculateNextMatrix();
  overwriteCurrentMatrixWithNextMatrix();
}


/**
 * @brief For each cell in a given matrix, checks the cell's neighbours and
 * applies Game Of Life's rules. Also, decides the fate of the examined cell.
 **/
void GameBoard::calculateNextMatrix(void)
{
  for (int row = 0; row != m_gameOptions.getNumOfRows(); ++row)
  {
    for (int col = 0; col != m_gameOptions.getNumOfCols(); ++col)
    {
      int aliveNeighboursCounter = countNumOfAliveNeighbours(row, col);
      applyGameRules(row, col, aliveNeighboursCounter);
    }
  }
}


void GameBoard::overwriteCurrentMatrixWithNextMatrix(void)
{
  if (m_currentMatrix != m_nextMatrix)
    m_currentMatrix = m_nextMatrix;
  else
    m_gameManager.stopTheTimer();
}


/**
 * @brief Receives mouse position (x, y) from the front-end. Calculates every cell's position on the
 * game board, and toggles whichever cell the mouse is currently interacting with. Until mouse exits
 * a cell, locks that cell to prevent rapid-fire toggling.
 *
 * @param mouseX mouse x position on the game board (coming from the front-end)
 * @param mouseY mouse y position on the game board (coming from the front-end)
 **/
void GameBoard::toggleCellStatusBecauseOfMouseInteraction(int mouseX, int mouseY)
{
  for (int row = 0; row != m_gameOptions.getNumOfRows(); ++row)
  {
    for (int col = 0; col != m_gameOptions.getNumOfCols(); ++col)
    {
      int currentCellUpperLeftVertexPosition_x = m_gameOptions.getSquareSpacing() + col * (m_gameOptions.getSquareSize() + m_gameOptions.getSquareSpacing());
      int currentCellUpperLeftVertexPosition_y = m_gameOptions.getSquareSpacing() + row * (m_gameOptions.getSquareSize() + m_gameOptions.getSquareSpacing());
      int currentCellLowerRghtVertexPosition_x = currentCellUpperLeftVertexPosition_x + m_gameOptions.getSquareSize(); // simple calculation because the cell is a square
      int currentCellLowerRghtVertexPosition_y = currentCellUpperLeftVertexPosition_y + m_gameOptions.getSquareSize(); // simple calculation because the cell is a square

      auto isMouseInCurrentCell = [mouseX, mouseY, currentCellUpperLeftVertexPosition_x, currentCellUpperLeftVertexPosition_y, currentCellLowerRghtVertexPosition_x, currentCellLowerRghtVertexPosition_y]()
      {
        return (    mouseX >= currentCellUpperLeftVertexPosition_x && mouseX <= currentCellLowerRghtVertexPosition_x
                &&  mouseY >= currentCellUpperLeftVertexPosition_y && mouseY <= currentCellLowerRghtVertexPosition_y );
      };

      if (isMouseInCurrentCell())
      {
        m_currentMatrix[row][col].toggle();
        m_currentMatrix[row][col].lockToggling();
      }
      else
      {
        m_currentMatrix[row][col].unlockToggling();
      }
    }
  }
}


void GameBoard::unlockToggling(void)
{
  for (int row = 0; row != m_gameOptions.getNumOfRows(); ++row)
  {
    for (int col = 0; col != m_gameOptions.getNumOfCols(); ++col)
    {
      m_currentMatrix[row][col].unlockToggling();
    }
  }
}


void GameBoard::flagBoardForResizing(void)
{
  m_boardNeedsResizing = true;
}


bool GameBoard::doesBoardNeedResizing(void) const
{
  return m_boardNeedsResizing;
}


void GameBoard::resizeGameBoard(void)
{
  int newNumOfRows = m_gameOptions.getNumOfRows();
  int newNumOfCols = m_gameOptions.getNumOfCols();

  // Resize rows
  m_currentMatrix.resize(newNumOfRows);
  m_nextMatrix.resize(newNumOfRows);

  // Resize cols
  for (int row = 0; row != newNumOfRows; ++row)
  {
    m_currentMatrix[row].resize(newNumOfCols);
    m_nextMatrix[row].resize(newNumOfCols);
  }
}


int GameBoard::countNumOfAliveNeighbours(int row, int col)
{
  int aliveNeighboursCounter = 0;

  if (isNeighbourWithinBounds(row - 1, col - 1) && isNeighbourAlive(row - 1, col - 1) )
    ++aliveNeighboursCounter; // Alive neighbour found: above left

  if (isNeighbourWithinBounds(row - 1, col) && isNeighbourAlive(row - 1, col) )
    ++aliveNeighboursCounter; // Alive neighbour found: above

  if (isNeighbourWithinBounds(row - 1, col + 1) && isNeighbourAlive(row - 1, col + 1) )
    ++aliveNeighboursCounter; // Alive neighbour found: above right

  if (isNeighbourWithinBounds(row, col - 1) && isNeighbourAlive(row, col - 1) )
    ++aliveNeighboursCounter; // Alive neighbour found: left

  if (isNeighbourWithinBounds(row, col + 1) && isNeighbourAlive(row, col + 1) )
    ++aliveNeighboursCounter; // Alive neighbour found: right

  if (isNeighbourWithinBounds(row + 1, col - 1) && isNeighbourAlive(row + 1, col - 1) )
    ++aliveNeighboursCounter; // Alive neighbour found: below Left

  if (isNeighbourWithinBounds(row + 1, col) && isNeighbourAlive(row + 1, col) )
    ++aliveNeighboursCounter; // Alive neighbour found: below

  if (isNeighbourWithinBounds(row + 1, col + 1) && isNeighbourAlive(row + 1, col + 1) )
    ++aliveNeighboursCounter; // Alive neighbour found: below right

  return aliveNeighboursCounter;
}


/**
 * @brief Applying Game of Life's rules
 **/
void GameBoard::applyGameRules(int row, int col, int aliveNeighboursCounter)
{
  const bool rule_1 = aliveNeighboursCounter == m_gameOptions.getDeadOrAliveLowerThreshold() || aliveNeighboursCounter == m_gameOptions.getDeadOrAliveUpperThreshold();
  const bool rule_2 = aliveNeighboursCounter == m_gameOptions.getDeadOrAliveUpperThreshold();

  if (m_currentMatrix[row][col].isAlive())
  {
    if (rule_1)
    {
      // Rule 1: any live cell with two or three live neighbours survives.
      m_nextMatrix[row][col].revive();
    }
    else
    {
      // Rule 3: all other live cells die in the next generation. Similarly, all other dead cells stay dead.
      m_nextMatrix[row][col].kill();
    }
  }
  else
  {
    if (rule_2)
    {
      // Rule 2: Any dead cell with three live neighbours becomes a live cell.
      m_nextMatrix[row][col].revive();
    }
    else
    {
      // Rule 3: all other dead cells stay dead.
      m_nextMatrix[row][col].kill();
    }
  }
}


bool GameBoard::isNeighbourWithinBounds(int row, int col)
{
  return ( row >= 0 && col >= 0 && row < m_gameOptions.getNumOfRows() && col < m_gameOptions.getNumOfCols() );
}


bool GameBoard::isNeighbourAlive(int row, int col)
{
  return ( m_currentMatrix[row][col].isAlive() );
}