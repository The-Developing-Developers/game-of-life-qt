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
  m_futureMatrix = new Cell*[m_numOfRows];

  // Number of cols
  for (int i = 0; i != m_numOfRows; ++i)
  {
    m_currentMatrix[i] = new Cell[m_numOfCols];
    m_futureMatrix[i] = new Cell[m_numOfCols];
  }

  qDebug() << __func__ << ": Square grid created.";
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


/**
 * @brief For each cell in a given matrix, checks the cell's neighbours and
 * applies Game Of Life's rules. Also, decides the fate of the examined cell.
 **/
void Grid::calculateNextGen(Cell** OldMatrix, Cell** NewMatrix)
{
  for (int i = 0; i < m_numOfRows; ++i)
  {
    for (int j = 0; j < m_numOfCols; ++j)
    {
      size_t AliveNeighboursCounter = 0;

      // Investigate neighbours
      if (isNeighbourWithinBounds(i - 1, j - 1) && isNeighbourAlive(OldMatrix, i - 1, j - 1) )
      {
        // Above left
        ++AliveNeighboursCounter;
      }
      else {;}

      if (isNeighbourWithinBounds(i - 1, j) && isNeighbourAlive(OldMatrix, i - 1, j) )
      {
        // Above
        ++AliveNeighboursCounter;
      }
      else {;}

      if (isNeighbourWithinBounds(i - 1, j + 1) && isNeighbourAlive(OldMatrix, i - 1, j + 1) )
      {
        // Above right
        ++AliveNeighboursCounter;
      }
      else {;}

      if (isNeighbourWithinBounds(i, j - 1) && isNeighbourAlive(OldMatrix, i, j - 1) )
      {
        // Left
        ++AliveNeighboursCounter;
      }
      else {;}

      if (isNeighbourWithinBounds(i, j + 1) && isNeighbourAlive(OldMatrix, i, j + 1) )
      {
        // Right
        ++AliveNeighboursCounter;
      }
      else {;}

      if (isNeighbourWithinBounds(i + 1, j - 1) && isNeighbourAlive(OldMatrix, i + 1, j - 1) )
      {
        // Below Left
        ++AliveNeighboursCounter;
      }
      else {;}

      if (isNeighbourWithinBounds(i + 1, j) && isNeighbourAlive(OldMatrix, i + 1, j) )
      {
        // Below
        ++AliveNeighboursCounter;
      }
      else {;}

      if (isNeighbourWithinBounds(i + 1, j + 1) && isNeighbourAlive(OldMatrix, i + 1, j + 1) )
      {
        // Below right
        ++AliveNeighboursCounter;
      }
      else {;}


      // Calculating next generation
      if (OldMatrix[i][j].isAlive())
      {
        if (AliveNeighboursCounter == m_DeadOrAliveLowerThreshold || AliveNeighboursCounter == m_DeadOrAliveUpperThreshold)
        {
          // Rule 1: any live cell with two or three live neighbours survives.
          NewMatrix[i][j].revive();
        }
        else
        {
          // Rule 3: all other live cells die in the next generation. Similarly, all other dead cells stay dead.
          NewMatrix[i][j].kill();
        }
      }
      else
      {
        // Analysing dead cells

        if (AliveNeighboursCounter == m_DeadOrAliveUpperThreshold)
        {
          // Rule 2: Any dead cell with three live neighbours becomes a live cell.
          NewMatrix[i][j].revive();
        }
        else
        {
          NewMatrix[i][j].kill();
        }
      }
    } // for loop
  } // for loop
}


bool Grid::isNeighbourWithinBounds(int i, int j)
{
  return ( i >= 0 && j >= 0 && i < m_numOfRows && j < m_numOfRows );
}


bool Grid::isNeighbourAlive(Cell** OldMatrix, int i, int j)
{
  return ( OldMatrix[i][j].isAlive() );
}


void Grid::recalculateBoard(void)
{
  qDebug() << __func__ << "Recalculating board...";

  for (size_t row = 0; row != m_numOfRows; ++row)
  {
    for (size_t col = 0; col != m_numOfCols; ++col)
    {
      m_currentMatrix[row][col] = m_futureMatrix[row][col];
    }
  }

  if (!m_invertOrder)
  {
    qDebug() << __func__ << "Calculating direct order...";
    calculateNextGen(m_currentMatrix, m_futureMatrix);

    m_invertOrder = false;
  }
  else
  {
    qDebug() << __func__ << "Calculating reverse order...";
    calculateNextGen(m_futureMatrix, m_currentMatrix);

    m_invertOrder = true;
  }
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

  // TODO: test
  if (m_currentMatrix[row][col].isAlive())
    qDebug() << __func__ << ": Cell (" << row << "," << col << "), index" << cellIndex << ", is alive";
  else
    qDebug() << __func__ << ": Cell (" << row << "," << col << "), index" << cellIndex << ", is not alive";
}


bool Grid::getCellStatus(int cellIndex)
{
  std::pair<int, int> rowCol = getRowColFromIndex(cellIndex);
  int row = rowCol.first;
  int col = rowCol.second;
  if (!m_invertOrder)
  {
    qDebug() << __func__ << "Order not inverted";
    // return m_currentMatrix[row][col].isAlive();
    return m_futureMatrix[row][col].isAlive();
  }
  else
  {
    qDebug() << __func__ << "Order inverted";
    return m_futureMatrix[row][col].isAlive();
  }
}
