/**
 * @file gameboard.hpp
 *
 * @brief The back-end logic and calculations are performed by this class.
 **/

#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <utility> // `std::pair`
#include <QVector>

class GameManager;
class GameOptions;
class Cell;

/**
 * @brief Creates a square grid populated with cells. Minimum size given by `m_MinMatrixSize`. \n
 * The back-end logic and calculations are performed by this class. \n
 * The game grid is represented in the back-end by a matrix (a `QVector` of `QVector`) of `Cell`s. The current matrix (`m_currMatrix`) is
 * the one currently displayed by the front-end, whereas the next matrix (`m_nextMatrix`) is calculated by the game logic (following the
 * Game Of Life's rules) and will replace the current matrix at the successive iteration of the game, when the timer in the front-end has
 * expired.
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
  void setCurrentPattern    (const QVector<QVector<bool>>& newPattern);
  void toggleCellStatusBecauseOfMouseInteraction(int mouseX, int mouseY);

private:

  void calculateNextMatrix                  (void);
  void overwriteCurrentMatrixWithNextMatrix (void);
  bool isNeighbourWithinBounds              (int row, int col);
  bool isNeighbourAlive                     (int row, int col);
  // int  getIndexFromRowCol                   (int row, int col); // TODO: unused
  int  countNumOfAliveNeighbours            (int row, int col);
  void applyGameRules                       (int row, int col, int aliveNeighboursCounter);
  std::pair<int, int> getRowColFromIndex    (int cellIndex);

  QVector<QVector<Cell>>  m_currMatrix; // TODO: consider using a faster data type instead of `QVector<QVector<Cell>>`, such as a fixed size array (`std::array<Cell>`) to be managed manually even for what concerns the second dimension
  QVector<QVector<Cell>>  m_nextMatrix;
  GameManager&            m_gameManager; // This reference is used to exchange data with the `GameManager`
  GameOptions&            m_gameOptions; // This reference is used to exchange data with the `GameOptions`
};

#endif // GAMEBOARD_HPP