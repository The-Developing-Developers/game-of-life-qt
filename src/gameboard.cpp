#include "gameboard.hpp"
#include "gameoptions.hpp"
#include "cell.hpp"
#include "gamemanager.hpp"

GameBoard::GameBoard(GameManager& gameManager)
  : m_gameManager(gameManager)
  , m_gameOptions(m_gameManager.getGameOptions())
{
  const int numOfRows = m_gameOptions.getNumOfRows();
  const int numOfCols = m_gameOptions.getNumOfCols();

  // Number of rows
  m_currMatrix.resize(numOfRows);
  m_nextMatrix.resize(numOfRows);

  // Number of cols
  for (int i = 0; i != numOfRows; ++i)
  {
    m_currMatrix[i].resize(numOfCols);
    m_nextMatrix[i].resize(numOfCols);
  }
}


GameBoard::~GameBoard(void)
{;}


// // TODO: unused
// int GameBoard::getIndexFromRowCol(int row, int col)
// {
//   return row * m_gameOptions.getNumOfCols() + col;
// }


/**
 * @brief Receives an index from the QML front-end and returns the correspondent position inside the current game matrix.
 *
 * @param cellIndex index coming from the QML front-end, when it needs to access a certain cell in the game grid.
 * @return `std::pair<int, int>` The index is transformed into a pair of `int` values, representing the row and column of the current game
 * matrix respectively.
 **/
std::pair<int, int> GameBoard::getRowColFromIndex(int cellIndex)
{
  int row = 0;
  int col = 0;

  // If `cellIndex` is 0, the loop is skipped
  for (int i = 0; i != cellIndex; ++i)
  {
    ++col;

    // Last element of the column has been encountered: go to the next row and reset the column number
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
  return m_currMatrix[row][col].isAlive();
}


void GameBoard::clearBoard(void)
{
  for (int row = 0; row != m_gameOptions.getNumOfRows(); ++row)
  {
    for (int col = 0; col != m_gameOptions.getNumOfCols(); ++col)
    {
      m_currMatrix[row][col].kill();
      m_nextMatrix[row][col].kill();
    }
  }
}


void GameBoard::recalculateBoard(void)
{
  calculateNextMatrix();
  overwriteCurrentMatrixWithNextMatrix();
}


/**
 * @brief For each cell in a given matrix, checks the cell's neighbours and applies Game Of Life's rules. Also, decides the fate of the
 * examined cell.
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


/**
 * @brief If the newly calculated matrix is actually different from the previous one, the new one replaces the old one and the game cycle
 * continues. Otherwise, it means that the game has come to a halt (for example because all the cells have died, or an equilibrium point has
 * been reached), and the game timer must be stopped.
 **/
void GameBoard::overwriteCurrentMatrixWithNextMatrix(void)
{
  if (m_currMatrix != m_nextMatrix)
    m_currMatrix = m_nextMatrix;
  else
    m_gameManager.stopTheTimer();
}


/**
 * @brief Receives mouse position (x, y) from the front-end. Calculates every cell's position on the game board, and toggles whichever cell
 * the mouse is currently interacting with. Until mouse exits a cell, locks that cell to prevent rapid-fire toggling.
 *
 * @param mouseX mouse x position on the game board (coming from the front-end)
 * @param mouseY mouse y position on the game board (coming from the front-end)
 **/
void GameBoard::toggleCellStatusBecauseOfMouseInteraction(int mouseX, int mouseY)
{
  // TODO: instead of constantly recalculating the position of every single cell, consider making this calculation whenever the game grid is
  // created or resized, store the newly calculated positions, and then read the positions from the storage.
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
        m_currMatrix[row][col].toggle();
        m_currMatrix[row][col].lockToggling();
      }
      else
      {
        m_currMatrix[row][col].unlockToggling();
      }
    }
  }
}


// TODO: since this function unlocks the toggling for all of the cells in the board, consider renaming it to something like
// `unlockAllCells`, because the homonymous function in `Cell` (`Cell::unlockToggling`) only unlocks a single cell, and sharing the same
// name could generate confusion.
void GameBoard::unlockToggling(void)
{
  for (int row = 0; row != m_gameOptions.getNumOfRows(); ++row)
  {
    for (int col = 0; col != m_gameOptions.getNumOfCols(); ++col)
    {
      m_currMatrix[row][col].unlockToggling();
    }
  }
}


void GameBoard::resizeGameBoard(void)
{
  // Here, the number of rows and cols has just been changed by the user in the options screen, so we can safely read from `m_gameOptions`.
  int newNumOfRows = m_gameOptions.getNumOfRows(); // TODO: add `const`
  int newNumOfCols = m_gameOptions.getNumOfCols(); // TODO: add `const`

  // Resize rows
  m_currMatrix.resize(newNumOfRows);
  m_nextMatrix.resize(newNumOfRows);

  // Resize cols
  for (int row = 0; row != newNumOfRows; ++row)
  {
    m_currMatrix[row].resize(newNumOfCols);
    m_nextMatrix[row].resize(newNumOfCols);
  }
}


void GameBoard::setCurrentPattern(const QVector<QVector<bool>>& newPattern)
{
  const int numOfRows = m_gameOptions.getNumOfRows();
  const int numOfCols = m_gameOptions.getNumOfCols();

  for (int row = 0; row != numOfRows; ++row)
  {
    for (int col = 0; col != numOfCols; ++col)
    {
      if (newPattern[row][col])
        m_currMatrix[row][col].revive();
      else
        m_currMatrix[row][col].kill();
    }
  }

  for (auto& rowOfCells : m_nextMatrix)
  {
    for (auto& cell : rowOfCells)
    {
      cell.kill();
    }
  }
}


/**
 * @brief Used to apply the rules of the Game of Life. A cell becomes dead or alive in the next generation based on the number of dead or
 * alive neighbouring cells.
 *
 * @param row The row number of the currently analysed cell.
 * @param col The column number of the currently analysed cell.
 * @return `int` The total number of alive neighbours for the currently analysed cell.
 **/
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
 * @brief Applies Game of Life's rules for a single cell, based on the number of dead or alive neighbours.
 **/
void GameBoard::applyGameRules(int row, int col, int aliveNeighboursCounter)
{
  const bool rule_1 = aliveNeighboursCounter == m_gameOptions.getDeadOrAliveLowerThreshold() || aliveNeighboursCounter == m_gameOptions.getDeadOrAliveUpperThreshold();
  const bool rule_2 = aliveNeighboursCounter == m_gameOptions.getDeadOrAliveUpperThreshold();

  if (m_currMatrix[row][col].isAlive())
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
  return ( m_currMatrix[row][col].isAlive() );
}
