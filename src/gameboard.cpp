#include <QDebug>
#include "gameboard.hpp"

/**
 * @brief Construct a new GameBoard object with custom size.
 **/
GameBoard::GameBoard(int numOfRows, int numOfCols, int squareSize, int squareSpacing)
  : m_numOfRows(numOfRows), m_numOfCols(numOfCols), m_squareSize(squareSize), m_squareSpacing(squareSpacing)
{
  // Number of rows
  m_currentMatrix = new Cell*[m_numOfRows];
  m_futureMatrix  = new Cell*[m_numOfRows];

  // Number of cols
  for (int i = 0; i != m_numOfRows; ++i)
  {
    m_currentMatrix[i] = new Cell[m_numOfCols];
    m_futureMatrix[i] = new Cell[m_numOfCols];
  }

  m_isInitialised = true;
}


GameBoard::~GameBoard(void)
{
  if (!m_isInitialised)
  {
    return;
  }

  for (int i = 0; i != m_numOfRows; ++i)
  {
    delete[] m_currentMatrix[i];
    delete[] m_futureMatrix[i];
    m_currentMatrix[i] = nullptr;
    m_futureMatrix[i] = nullptr;
  }

  delete[] m_currentMatrix;
  delete[] m_futureMatrix;
  m_currentMatrix = nullptr;
  m_futureMatrix = nullptr;
}


int GameBoard::getIndexFromRowCol(int row, int col)
{
  return row * m_numOfCols + col;
}


std::pair<int, int> GameBoard::getRowColFromIndex(int cellIndex)
{
  int row = 0;
  int col = 0;

  for (size_t i = 0; i != cellIndex; ++i)
  {
    ++col;

    if (col == m_numOfCols)
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
  for (size_t row = 0; row != m_numOfRows; ++row)
  {
    for (size_t col = 0; col != m_numOfCols; ++col)
    {
      m_currentMatrix[row][col].kill();
      m_futureMatrix [row][col].kill();
    }
  }
}


void GameBoard::recalculateBoard(void)
{
  calculateFutureMatrix();
  overwriteCurrentMatrixWithFutureMatrix();
}


/**
 * @brief For each cell in a given matrix, checks the cell's neighbours and
 * applies Game Of Life's rules. Also, decides the fate of the examined cell.
 **/
void GameBoard::calculateFutureMatrix(void)
{
  for (int i = 0; i < m_numOfRows; ++i)
  {
    for (int j = 0; j < m_numOfCols; ++j)
    {
      size_t AliveNeighboursCounter = 0;

      // Investigate neighbours

      if (isNeighbourWithinBounds(i - 1, j - 1) && isNeighbourAlive(i - 1, j - 1) )
      {
        ++AliveNeighboursCounter; // Above left
      }
      else {;}

      if (isNeighbourWithinBounds(i - 1, j) && isNeighbourAlive(i - 1, j) )
      {
        ++AliveNeighboursCounter; // Above
      }
      else {;}

      if (isNeighbourWithinBounds(i - 1, j + 1) && isNeighbourAlive(i - 1, j + 1) )
      {
        ++AliveNeighboursCounter; // Above right
      }
      else {;}

      if (isNeighbourWithinBounds(i, j - 1) && isNeighbourAlive(i, j - 1) )
      {
        ++AliveNeighboursCounter; // Left
      }
      else {;}

      if (isNeighbourWithinBounds(i, j + 1) && isNeighbourAlive(i, j + 1) )
      {
        ++AliveNeighboursCounter; // Right
      }
      else {;}

      if (isNeighbourWithinBounds(i + 1, j - 1) && isNeighbourAlive(i + 1, j - 1) )
      {
        ++AliveNeighboursCounter; // Below Left
      }
      else {;}

      if (isNeighbourWithinBounds(i + 1, j) && isNeighbourAlive(i + 1, j) )
      {
        ++AliveNeighboursCounter; // Below
      }
      else {;}

      if (isNeighbourWithinBounds(i + 1, j + 1) && isNeighbourAlive(i + 1, j + 1) )
      {
        ++AliveNeighboursCounter; // Below right
      }
      else {;}

      // Calculating next generation (applying game's rules)

      if (m_currentMatrix[i][j].isAlive())
      {
        // TODO: replace conditions with constants for readability?
        if (AliveNeighboursCounter == m_DeadOrAliveLowerThreshold || AliveNeighboursCounter == m_DeadOrAliveUpperThreshold)
        {
          // Rule 1: any live cell with two or three live neighbours survives.
          m_futureMatrix[i][j].revive(); // TODO: superfluous? Cell is already alive in this `if`
        }
        else
        {
          // Rule 3: all other live cells die in the next generation. Similarly, all other dead cells stay dead.
          m_futureMatrix[i][j].kill();
        }
      }
      else
      {
        // Analysing dead cells

        if (AliveNeighboursCounter == m_DeadOrAliveUpperThreshold)
        {
          // Rule 2: Any dead cell with three live neighbours becomes a live cell.
          m_futureMatrix[i][j].revive();
        }
        else
        {
          m_futureMatrix[i][j].kill(); // TODO: superfluous? Cell is already dead in this `else`
        }
      }
    } // for loop
  } // for loop
}


bool GameBoard::isNeighbourWithinBounds(int row, int col)
{
  return ( row >= 0 && col >= 0 && row < m_numOfRows && col < m_numOfCols );
}


bool GameBoard::isNeighbourAlive(int row, int col)
{
  return ( m_currentMatrix[row][col].isAlive() );
}


void GameBoard::overwriteCurrentMatrixWithFutureMatrix(void)
{
  for (size_t row = 0; row != m_numOfRows; ++row)
  {
    for (size_t col = 0; col != m_numOfCols; ++col)
    {
      m_currentMatrix[row][col] = m_futureMatrix[row][col];
    }
  }
}


/**
 * @brief Receives mouse position (x, y) from the front-end. Calculates every cell's position on the
 * game board, and toggles whichever cell the mouse is currently interacting with.
 *
 * @param mouseX mouse x position on the game board (coming from the front-end)
 * @param mouseY mouse y position on the game board (coming from the front-end)
 **/
void GameBoard::toggleCellStatusBecauseOfMouseInteraction(int mouseX, int mouseY)
{
  for (int row = 0; row != m_numOfRows; ++row)
  {
    for (int col = 0; col != m_numOfCols; ++col)
    {
      int currentCellUpperLeftVertexPosition_x = m_squareSpacing + col * (m_squareSize + m_squareSpacing);
      int currentCellUpperLeftVertexPosition_y = m_squareSpacing + row * (m_squareSize + m_squareSpacing);
      int currentCellLowerRghtVertexPosition_x = currentCellUpperLeftVertexPosition_x + m_squareSize; // simple calculation because the cell is a square
      int currentCellLowerRghtVertexPosition_y = currentCellUpperLeftVertexPosition_y + m_squareSize; // simple calculation because the cell is a square

      auto isMouseInCurrentCell = [&mouseX, &mouseY, &currentCellUpperLeftVertexPosition_x, &currentCellUpperLeftVertexPosition_y, &currentCellLowerRghtVertexPosition_x, &currentCellLowerRghtVertexPosition_y]()
      {
        return (    mouseX >= currentCellUpperLeftVertexPosition_x && mouseX <= currentCellLowerRghtVertexPosition_x
                &&  mouseY >= currentCellUpperLeftVertexPosition_y && mouseY <= currentCellLowerRghtVertexPosition_y );
      };

      if (isMouseInCurrentCell())
      {
        m_currentMatrix[row][col].toggle();
        m_currentMatrix[row][col].m_hasJustBeenToggled = true; // TODO: must not access this directly
      }
      else
      {
        m_currentMatrix[row][col].m_hasJustBeenToggled = false; // TODO: must not access this directly
      }
    }
  }
}


void GameBoard::clearHasJustBeenToggledFlag(void)
{
  for (int row = 0; row != m_numOfRows; ++row)
  {
    for (int col = 0; col != m_numOfCols; ++col)
    {
      m_currentMatrix[row][col].m_hasJustBeenToggled = false; // TODO: must not access this directly
    }
  }
}