#include <QDebug>
#include "grid.hpp"

/**
 * @brief Construct a new Grid object with custom size.
 **/
Grid::Grid(int numOfRows, int numOfCols)
  : m_numOfRows(numOfRows), m_numOfCols(numOfCols)
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

  qDebug() << __func__ << ": Square grid created, with" << m_numOfRows * m_numOfCols << "squares.";
}


Grid::~Grid(void)
{
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

  qDebug() << __func__ << ": Square grid destroyed.";
}


int Grid::getIndexFromRowCol(int row, int col)
{
  return row * m_numOfCols + col;
}


std::pair<int, int> Grid::getRowColFromIndex(int cellIndex)
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


bool Grid::getCellStatus(int cellIndex)
{
  std::pair<int, int> rowCol = getRowColFromIndex(cellIndex);
  int row = rowCol.first;
  int col = rowCol.second;
  return m_currentMatrix[row][col].isAlive();
}


void Grid::setCellStatus(int cellIndex, bool isAlive)
{
  // qDebug() << __func__ << ": index: " << index << "; isAlive: " << isAlive;
  std::pair<int, int> rowCol = getRowColFromIndex(cellIndex);
  int row = rowCol.first;
  int col = rowCol.second;

  if (isAlive)
    m_currentMatrix[row][col].revive();
  else
    m_currentMatrix[row][col].kill();

  // // TODO: debug
  // if (m_currentMatrix[row][col].isAlive())
  //   qDebug() << __func__ << ": Cell (" << row << "," << col << "), index" << cellIndex << ", is alive";
  // else
  //   qDebug() << __func__ << ": Cell (" << row << "," << col << "), index" << cellIndex << ", is not alive";
}


void Grid::clearBoard(void)
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


void Grid::recalculateBoard(void)
{
  // qDebug() << __func__ << "Recalculating board...";
  calculateFutureMatrix();
  overwriteCurrentMatrixWithFutureMatrix();
}


/**
 * @brief For each cell in a given matrix, checks the cell's neighbours and
 * applies Game Of Life's rules. Also, decides the fate of the examined cell.
 **/
void Grid::calculateFutureMatrix(void)
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
        if (AliveNeighboursCounter == m_DeadOrAliveLowerThreshold || AliveNeighboursCounter == m_DeadOrAliveUpperThreshold)
        {
          // Rule 1: any live cell with two or three live neighbours survives.
          m_futureMatrix[i][j].revive();
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
          m_futureMatrix[i][j].kill();
        }
      }
    } // for loop
  } // for loop
}


bool Grid::isNeighbourWithinBounds(int row, int col)
{
  return ( row >= 0 && col >= 0 && row < m_numOfRows && col < m_numOfCols );
}


bool Grid::isNeighbourAlive(int row, int col)
{
  return ( m_currentMatrix[row][col].isAlive() );
}


void Grid::overwriteCurrentMatrixWithFutureMatrix(void)
{
  for (size_t row = 0; row != m_numOfRows; ++row)
  {
    for (size_t col = 0; col != m_numOfCols; ++col)
    {
      m_currentMatrix[row][col] = m_futureMatrix[row][col];
    }
  }
}