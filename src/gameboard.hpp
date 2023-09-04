#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <utility>
#include <QVector>

class Backend;
class GameOptions;
class Cell;

/**
 * @brief Create a square grid populated with cells. Minimum size given by "m_MinMatrixSize".
 **/
class GameBoard
{
public:

   GameBoard(Backend& backend);
  ~GameBoard(void);

  void recalculateBoard(void);

  bool getCellStatus        (int cellIndex);
  void clearBoard           (void);
  void unlockToggling       (void);
  void flagBoardForResizing (void);
  bool doesBoardNeedResizing(void) const;
  void resizeGameBoard      (void);
  void toggleCellStatusBecauseOfMouseInteraction(int mouseX, int mouseY);

private:

  void calculateNextMatrix                  (void);
  void overwriteCurrentMatrixWithNextMatrix (void);
  bool isNeighbourWithinBounds              (int row, int col);
  bool isNeighbourAlive                     (int row, int col);
  int  getIndexFromRowCol                   (int row, int col);
  int  countNumOfAliveNeighbours            (int row, int col);
  void applyGameRules                       (int row, int col, int aliveNeighboursCounter);
  std::pair<int, int> getRowColFromIndex    (int cellIndex);

  QVector<QVector<Cell>>  m_currentMatrix;
  QVector<QVector<Cell>>  m_nextMatrix;
  Backend&                m_backend;
  GameOptions&            m_gameOptions;
  bool                    m_boardNeedsResizing = false;
};

#endif // GAMEBOARD_HPP