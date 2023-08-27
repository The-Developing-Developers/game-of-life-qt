#ifndef GRID_HPP
#define GRID_HPP

#include "cell.hpp"

/**
 * @brief Create a square grid populated with cells. Minimum size given by "m_MinMatrixSize".
 **/
class Grid
{
public:

   Grid(int numOfRows, int numOfCols);
  ~Grid(void);

  void recalculateBoard(void);

  bool getCellStatus(int cellIndex);
  void setCellStatus(int index, bool isAlive);
  void clearBoard    (void);

private:

  void calculateFutureMatrix                  (void);
  void overwriteCurrentMatrixWithFutureMatrix (void);
  bool isNeighbourWithinBounds                (int row, int col);
  bool isNeighbourAlive                       (int row, int col);
  int  getIndexFromRowCol                     (int row, int col);
  std::pair<int, int> getRowColFromIndex      (int cellIndex);

  static constexpr size_t m_DeadOrAliveUpperThreshold = 3; // Game of Life's rule
  static constexpr size_t m_DeadOrAliveLowerThreshold = 2; // Game of Life's rule
  const int m_numOfRows;
  const int m_numOfCols;
  Cell**    m_currentMatrix;
  Cell**    m_futureMatrix;
  bool      m_isInitialised = false;
};

#endif // GRID_HPP