#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <utility>
#include <QVector>

class GameManager;
class GameOptions;
class Cell;

/**
 * @brief Create a square grid populated with cells. Minimum size given by "m_MinMatrixSize".
 **/
class GameBoard
{
public:

   GameBoard(GameManager& gameManager);
  ~GameBoard(void);

  void recalculateBoard(void);

  bool getCellStatus        (int cellIndex);
  void clearBoard           (void);
  void unlockToggling       (void);
  void resizeGameBoard      (void);
  void setCurrentPattern    (const QVector<QVector<bool>>);
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

  QVector<QVector<Cell>>  m_currMatrix;
  QVector<QVector<Cell>>  m_nextMatrix;
  GameManager&            m_gameManager;
  GameOptions&            m_gameOptions;
};

#endif // GAMEBOARD_HPP