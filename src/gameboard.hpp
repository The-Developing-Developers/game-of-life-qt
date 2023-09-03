#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <utility>
#include <QVector>
#include "cell.hpp"

class GameOptions;

/**
 * @brief Create a square grid populated with cells. Minimum size given by "m_MinMatrixSize".
 **/
class GameBoard
{
public:

   GameBoard(GameOptions& gameOptions);
  ~GameBoard(void);

  void recalculateBoard(void);

  bool getCellStatus              (int cellIndex);
  void clearBoard                 (void);
  void clearHasJustBeenToggledFlag(void);
  void flagBoardForReInit         (void);
  bool doesBoardNeedReInit        (void) const;
  void toggleCellStatusBecauseOfMouseInteraction(int mouseX, int mouseY);

  GameBoard saveGameBoardCopy(void);
  void      loadGameBoardCopy(const GameBoard& gameboard);

private:

  void calculateFutureMatrix                  (void);
  void overwriteCurrentMatrixWithFutureMatrix (void);
  bool isNeighbourWithinBounds                (int row, int col);
  bool isNeighbourAlive                       (int row, int col);
  int  getIndexFromRowCol                     (int row, int col);
  std::pair<int, int> getRowColFromIndex      (int cellIndex);

  QVector<QVector<Cell>>  m_currentMatrix;
  QVector<QVector<Cell>>  m_futureMatrix;
  GameOptions&            m_gameOptions;
  bool                    m_boardNeedsReinit = false;
};

#endif // GAMEBOARD_HPP