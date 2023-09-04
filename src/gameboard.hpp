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

  bool getCellStatus          (int cellIndex);
  void clearBoard             (void);
  void unlockToggling         (void);
  void flagBoardForResizing   (void);
  bool doesBoardNeedResizing  (void) const;
  void resizeGameBoard        (void);
  void toggleCellStatusBecauseOfMouseInteraction(int mouseX, int mouseY);

  GameBoard saveGameBoardCopy(void);
  void      loadGameBoardCopy(const GameBoard& gameboard);

private:

  void calculateFutureMatrix                  (void);
  void overwriteCurrentMatrixWithFutureMatrix (void);
  bool isNeighbourWithinBounds                (int row, int col);
  bool isNeighbourAlive                       (int row, int col);
  int  getIndexFromRowCol                     (int row, int col);
  int  countNumOfAliveNeighbours              (int row, int col);
  void calculateNextGeneration                (int row, int col, int aliveNeighboursCounter);
  std::pair<int, int> getRowColFromIndex      (int cellIndex);

  QVector<QVector<Cell>>  m_currentMatrix;
  QVector<QVector<Cell>>  m_futureMatrix;
  GameOptions&            m_gameOptions;
  bool                    m_boardNeedsReinit = false;
};

#endif // GAMEBOARD_HPP