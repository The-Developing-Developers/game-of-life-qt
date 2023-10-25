#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <qqmlintegration.h>
#include "gameboard.hpp"
#include "gameoptions.hpp"
#include "shapes.hpp"

class GameManager : public QObject
{
  Q_OBJECT
  QML_ELEMENT

public:

  explicit GameManager(QObject *parent = nullptr);
          ~GameManager(void);

  Q_PROPERTY(bool         isAnimationAllowed  READ getIsAnimationAllowed  WRITE setIsAnimationAllowed NOTIFY isAnimationAllowedChanged);
  Q_PROPERTY(int          numOfRows           READ getNumOfRows           WRITE setNumOfRows          NOTIFY numOfRowsChanged);
  Q_PROPERTY(int          numOfCols           READ getNumOfCols           WRITE setNumOfCols          NOTIFY numOfColsChanged);
  Q_PROPERTY(int          squareSize          READ getSquareSize          WRITE setSquareSize         NOTIFY squareSizeChanged);
  Q_PROPERTY(int          squareSpacing       READ getSquareSpacing       WRITE setSquareSpacing      NOTIFY squareSpacingChanged);
  Q_PROPERTY(int          timerPeriod         READ getTimerPeriod         WRITE setTimerPeriod        NOTIFY timerPeriodChanged);
  Q_PROPERTY(int          currentShapeIndex   READ getShapeIndex          WRITE setCurrentShape       NOTIFY shapeIndexChanged);
  Q_PROPERTY(QStringList  listOfShapes        READ getListOfShapes CONSTANT);

  Q_INVOKABLE void              clearBoard            (void);
  Q_INVOKABLE void              recalculateBoard      (void);
  Q_INVOKABLE int               getNumOfRows          (void)          const;
  Q_INVOKABLE int               getNumOfCols          (void)          const;
  Q_INVOKABLE int               getTimerPeriod        (void)          const;
  Q_INVOKABLE int               getSquareSize         (void)          const;
  Q_INVOKABLE int               getSquareSpacing      (void)          const;
  Q_INVOKABLE bool              getIsAnimationAllowed (void)          const;
  Q_INVOKABLE bool              getCellStatus         (int cellIndex) const;
  Q_INVOKABLE const QStringList getListOfShapes       (void)          const;
  Q_INVOKABLE int               getShapeIndex         (void)          const;
  Q_INVOKABLE void              setNumOfRows          (int numOfRows);
  Q_INVOKABLE void              setNumOfCols          (int numOfCols);
  Q_INVOKABLE void              setSquareSize         (int squareSize);
  Q_INVOKABLE void              setSquareSpacing      (int squareSpacing);
  Q_INVOKABLE void              setTimerPeriod        (int timerPeriod_ms);
  Q_INVOKABLE void              setIsAnimationAllowed (bool isAnimationAllowed);
  Q_INVOKABLE void              setCurrentShape       (int shapeIndex);
  Q_INVOKABLE void              backgroundInteracted  (int mouseX, int mouseY);
  Q_INVOKABLE void              backgroundReleased    (void);

  void          stopTheTimer  (void);
  GameOptions&  getGameOptions(void) const;

signals:

  void boardChanged             (void);
  void stopTimer                (void);
  void isAnimationAllowedChanged(void);
  void numOfRowsChanged         (int);
  void numOfColsChanged         (int);
  void squareSizeChanged        (int);
  void squareSpacingChanged     (int);
  void timerPeriodChanged       (int);
  void shapeIndexChanged        (int);

private:

  QScopedPointer<GameOptions>       m_gameOptions;
  QScopedPointer<GameBoard>         m_gameBoard;
  QScopedPointer<Shapes>            m_shapes;
  bool m_isAnimationAllowed;

  void resizeGameBoard(void);
};

#endif // GAMEMANAGER_H
