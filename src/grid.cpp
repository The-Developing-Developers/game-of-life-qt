#include <QDebug>
#include "grid.hpp"

/**
 * @brief Construct a new Grid object with custom size.
 **/
Grid::Grid(int numOfRows, int numOfCols)
  : m_numOfRows(numOfRows), m_numOfCols(numOfCols)
{
  // Number of rows
  m_matrix_1 = new Cell*[m_numOfRows];
  m_matrix_2 = new Cell*[m_numOfRows];

  // Number of cols
  for (int i = 0; i != m_numOfRows; ++i)
  {
    m_matrix_1[i] = new Cell[m_numOfCols];
    m_matrix_2[i] = new Cell[m_numOfCols];
  }

  qDebug() << __func__ << ": Square grid created.";
}


Grid::~Grid(void)
{
  for (int i = 0; i != m_numOfRows; ++i)
  {
    delete[] m_matrix_1[i];
    delete[] m_matrix_2[i];
    m_matrix_1[i] = nullptr;
    m_matrix_2[i] = nullptr;
  }

  delete[] m_matrix_1;
  delete[] m_matrix_2;
  m_matrix_1 = nullptr;
  m_matrix_2 = nullptr;

  qDebug() << __func__ << ": Square grid destroyed.";
}


/**
 * @brief Setup the starting condition of the game
 *
 * @param Row Row of the cell to revive
 * @param Col Column of the cell to revive
 **/
void Grid::SetStartingAliveCells(int Row, int Col) const
{
  m_matrix_1[Row][Col].Revive();
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
void Grid::CalculateNextGen(Cell** OldMatrix, Cell** NewMatrix)
{
  for (int i = 0; i < m_numOfRows; ++i)
  {
    for (int j = 0; j < m_numOfCols; ++j)
    {
      size_t AliveNeighboursCounter = 0;

      // Investigate neighbours
      if (IsNeighbourWithinBounds(i - 1, j - 1) && IsNeighbourAlive(OldMatrix, i - 1, j - 1) )
      {
        // Above left
        ++AliveNeighboursCounter;
      }
      else {;}

      if (IsNeighbourWithinBounds(i - 1, j) && IsNeighbourAlive(OldMatrix, i - 1, j) )
      {
        // Above
        ++AliveNeighboursCounter;
      }
      else {;}

      if (IsNeighbourWithinBounds(i - 1, j + 1) && IsNeighbourAlive(OldMatrix, i - 1, j + 1) )
      {
        // Above right
        ++AliveNeighboursCounter;
      }
      else {;}

      if (IsNeighbourWithinBounds(i, j - 1) && IsNeighbourAlive(OldMatrix, i, j - 1) )
      {
        // Left
        ++AliveNeighboursCounter;
      }
      else {;}

      if (IsNeighbourWithinBounds(i, j + 1) && IsNeighbourAlive(OldMatrix, i, j + 1) )
      {
        // Right
        ++AliveNeighboursCounter;
      }
      else {;}

      if (IsNeighbourWithinBounds(i + 1, j - 1) && IsNeighbourAlive(OldMatrix, i + 1, j - 1) )
      {
        // Below Left
        ++AliveNeighboursCounter;
      }
      else {;}

      if (IsNeighbourWithinBounds(i + 1, j) && IsNeighbourAlive(OldMatrix, i + 1, j) )
      {
        // Below
        ++AliveNeighboursCounter;
      }
      else {;}

      if (IsNeighbourWithinBounds(i + 1, j + 1) && IsNeighbourAlive(OldMatrix, i + 1, j + 1) )
      {
        // Below right
        ++AliveNeighboursCounter;
      }
      else {;}


      // Calculating next generation
      if (OldMatrix[i][j].IsAlive())
      {
        if (AliveNeighboursCounter == m_DeadOrAliveLowerThreshold || AliveNeighboursCounter == m_DeadOrAliveUpperThreshold)
        {
          // Rule 1: any live cell with two or three live neighbours survives.
          NewMatrix[i][j].Revive();
        }
        else
        {
          // Rule 3: all other live cells die in the next generation. Similarly, all other dead cells stay dead.
          NewMatrix[i][j].Kill();
        }
      }
      else
      {
        // Analysing dead cells

        if (AliveNeighboursCounter == m_DeadOrAliveUpperThreshold)
        {
          // Rule 2: Any dead cell with three live neighbours becomes a live cell.
          NewMatrix[i][j].Revive();
        }
        else
        {
          NewMatrix[i][j].Kill();
        }
      }
    } // for loop
  } // for loop
}


bool Grid::IsNeighbourWithinBounds(int i, int j)
{
  return ( i >= 0 && j >= 0 && i < m_numOfRows && j < m_numOfRows );
}


bool Grid::IsNeighbourAlive(Cell** OldMatrix, int i, int j)
{
  return ( OldMatrix[i][j].IsAlive() );
}


void Grid::recalculateBoard(void)
{
  qDebug() << __func__ << "Recalculating board...";

  for (size_t row = 0; row != m_numOfRows; ++row)
  {
    for (size_t col = 0; col != m_numOfCols; ++col)
    {
      m_matrix_1[row][col] = m_matrix_2[row][col];
    }
  }

  if (!m_invertOrder)
  {
    qDebug() << __func__ << "Calculating direct order...";
    CalculateNextGen(m_matrix_1, m_matrix_2);

    m_invertOrder = false;
  }
  else
  {
    qDebug() << __func__ << "Calculating reverse order...";
    CalculateNextGen(m_matrix_2, m_matrix_1);

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
    m_matrix_2[row][col].Revive();
    // m_matrix_1[row][col].Revive();
  else
    m_matrix_2[row][col].Kill();
    // m_matrix_1[row][col].Kill();

  // TODO: test
  if (m_matrix_2[row][col].IsAlive())
  // if (m_matrix_1[row][col].IsAlive())
    qDebug() << __func__ << ": Cell " << row << ", " << col << " is alive";
  else
    qDebug() << __func__ << ": Cell " << row << ", " << col << " is not alive";
}


bool Grid::getCellStatus(int cellIndex)
{
  std::pair<int, int> rowCol = getRowColFromIndex(cellIndex);
  int row = rowCol.first;
  int col = rowCol.second;
  if (!m_invertOrder)
  {
    qDebug() << __func__ << "Order not inverted";
    // return m_matrix_1[row][col].IsAlive();
    return m_matrix_2[row][col].IsAlive();
  }
  else
  {
    qDebug() << __func__ << "Order inverted";
    return m_matrix_2[row][col].IsAlive();
  }
}
