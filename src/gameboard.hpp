#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <utility>
#include "cell.hpp"

class GameOptions;

/**
 * @brief Create a square grid populated with cells. Minimum size given by "m_MinMatrixSize".
 **/
class GameBoard
{
public:

   GameBoard(GameOptions* gameOptions);
  ~GameBoard(void);

  void recalculateBoard(void);

  bool getCellStatus(int cellIndex);
  void clearBoard   (void);
  void toggleCellStatusBecauseOfMouseInteraction (int mouseX, int mouseY);
  void clearHasJustBeenToggledFlag(void);

private:

  void calculateFutureMatrix                  (void);
  void overwriteCurrentMatrixWithFutureMatrix (void);
  bool isNeighbourWithinBounds                (int row, int col);
  bool isNeighbourAlive                       (int row, int col);
  int  getIndexFromRowCol                     (int row, int col);
  std::pair<int, int> getRowColFromIndex      (int cellIndex);

  bool          m_isInitialised = false; // TODO: evaluate if this is necessary
  Cell**        m_currentMatrix;
  Cell**        m_futureMatrix;
  GameOptions*  m_gameOptions;
};

#endif // GAMEBOARD_HPP