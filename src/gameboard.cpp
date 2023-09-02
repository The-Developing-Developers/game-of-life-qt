#include "gameboard.hpp"
#include "gameoptions.hpp"

/**
 * @brief Construct a new GameBoard object with custom size.
 **/
GameBoard::GameBoard(GameOptions* gameOptions)
  : m_gameOptions(gameOptions)
{
  // Number of rows
  m_currentMatrix = new Cell*[m_gameOptions->getNumOfRows()];
  m_futureMatrix  = new Cell*[m_gameOptions->getNumOfRows()];

  // Number of cols
  for (int i = 0; i != m_gameOptions->getNumOfRows(); ++i)
  {
    m_currentMatrix[i] = new Cell[m_gameOptions->getNumOfCols()];
    m_futureMatrix[i]  = new Cell[m_gameOptions->getNumOfCols()];
  }

  m_isInitialised = true; // TODO: is it necessary?
}


GameBoard::~GameBoard(void)
{
  if (!m_isInitialised) // TODO: is it necessary?
  {
    return;
  }

  int numOfRows_initial = m_gameOptions->getNumOfRows_initial();
  for (int i = 0; i != numOfRows_initial; ++i)
  {
    delete[] m_currentMatrix[i];
    delete[] m_futureMatrix[i];
    m_currentMatrix[i] = nullptr;
    m_futureMatrix[i]  = nullptr;
  }

  delete[] m_currentMatrix;
  delete[] m_futureMatrix;
  m_currentMatrix = nullptr;
  m_futureMatrix  = nullptr;
}


int GameBoard::getIndexFromRowCol(int row, int col)
{
  return row * m_gameOptions->getNumOfCols() + col;
}


std::pair<int, int> GameBoard::getRowColFromIndex(int cellIndex)
{
  int row = 0;
  int col = 0;

  for (int i = 0; i != cellIndex; ++i)
  {
    ++col;

    if (col == m_gameOptions->getNumOfCols())
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
  for (int row = 0; row != m_gameOptions->getNumOfRows(); ++row)
  {
    for (int col = 0; col != m_gameOptions->getNumOfCols(); ++col)
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
  for (int i = 0; i < m_gameOptions->getNumOfRows(); ++i)
  {
    for (int j = 0; j < m_gameOptions->getNumOfCols(); ++j)
    {
      int AliveNeighboursCounter = 0;

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
        if (AliveNeighboursCounter == m_gameOptions->getDeadOrAliveLowerThreshold() || AliveNeighboursCounter == m_gameOptions->getDeadOrAliveUpperThreshold())
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

        if (AliveNeighboursCounter == m_gameOptions->getDeadOrAliveUpperThreshold())
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
  return ( row >= 0 && col >= 0 && row < m_gameOptions->getNumOfRows() && col < m_gameOptions->getNumOfCols() );
}


bool GameBoard::isNeighbourAlive(int row, int col)
{
  return ( m_currentMatrix[row][col].isAlive() );
}


void GameBoard::overwriteCurrentMatrixWithFutureMatrix(void)
{
  for (int row = 0; row != m_gameOptions->getNumOfRows(); ++row)
  {
    for (int col = 0; col != m_gameOptions->getNumOfCols(); ++col)
    {
      m_currentMatrix[row][col] = m_futureMatrix[row][col];
    }
  }
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
  for (int row = 0; row != m_gameOptions->getNumOfRows(); ++row)
  {
    for (int col = 0; col != m_gameOptions->getNumOfCols(); ++col)
    {
      int currentCellUpperLeftVertexPosition_x = m_gameOptions->getSquareSpacing() + col * (m_gameOptions->getSquareSize() + m_gameOptions->getSquareSpacing());
      int currentCellUpperLeftVertexPosition_y = m_gameOptions->getSquareSpacing() + row * (m_gameOptions->getSquareSize() + m_gameOptions->getSquareSpacing());
      int currentCellLowerRghtVertexPosition_x = currentCellUpperLeftVertexPosition_x + m_gameOptions->getSquareSize(); // simple calculation because the cell is a square
      int currentCellLowerRghtVertexPosition_y = currentCellUpperLeftVertexPosition_y + m_gameOptions->getSquareSize(); // simple calculation because the cell is a square

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


void GameBoard::clearHasJustBeenToggledFlag(void)
{
  for (int row = 0; row != m_gameOptions->getNumOfRows(); ++row)
  {
    for (int col = 0; col != m_gameOptions->getNumOfCols(); ++col)
    {
      m_currentMatrix[row][col].unlockToggling();
    }
  }
}