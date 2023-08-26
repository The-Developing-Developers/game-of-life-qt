#ifndef GRID_HPP
#define GRID_HPP

// #include <iostream>
// #include <string>
// #include <thread>
// #include <chrono>
// #include <limits>
#include "cell.hpp"

#define NDEBUG

/**
 * @brief Create a square grid populated with cells. Minimum size given by "m_MinMatrixSize".
 **/
class Grid
{
public:

  // enum class Figure
  // typedef enum Figure_
  // {
  //   Figure_Square = 0,
  //   Figure_Beehive,
  //   Figure_Blinker,
  //   Figure_Toad,
  //   Figure_Beacon,
  //   Figure_Pulsar,
  //   Figure_Glider,
  //   Figure_PentaDecathlon
  // } Figure_enum;

  // Figure_enum m_Figure_enum;

  // Grid(void);
  Grid(int numOfRows, int numOfCols);
  // Grid(int GridSize_, Figure_enum Figure_);

  ~Grid(void);

  void SetStartingAliveCells(int Row, int Col) const;


  // void StartGame(void);

  static size_t MinMatrixNumOfRows(void);
  void recalculateBoard(void);
  std::pair<int, int> getRowColFromIndex(int cellIndex); // TODO: mettere private
  int getIndexFromRowCol(int row, int col); // TODO: mettere private

  bool getCellStatus(int cellIndex);
  void setCellStatus(int index, bool isAlive);


private:

  void CalculateNextGen(Cell** OldMatrix, Cell** NewMatrix);
  bool IsNeighbourWithinBounds(int i, int j);
  bool IsNeighbourAlive(Cell** OldMatrix, int i, int j);
  // void InitialiseStartingFigure(Figure_enum m_Figure_enum);

  static constexpr size_t m_DeadOrAliveUpperThreshold = 3; // Game of Life's rule
  static constexpr size_t m_DeadOrAliveLowerThreshold = 2; // Game of Life's rule
  const int m_numOfRows;
  const int m_numOfCols;
  // Cell** m_Matrix;
  Cell** m_matrix_1;
  Cell** m_matrix_2;
  bool m_invertOrder = false;
};

#endif // GRID_HPP