#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <qqmlintegration.h>
#include "gameboard.hpp"
#include "gameoptions.hpp"
#include "patterns.hpp"

class GameManager : public QObject
{
  Q_OBJECT
  QML_ELEMENT

public:

  explicit GameManager(QObject *parent = nullptr);
          ~GameManager(void);

  Patterns* getPatternPointerForQmlContext(void) const;

  Q_PROPERTY(bool         isAnimationAllowed    READ getIsAnimationAllowed  WRITE setIsAnimationAllowed NOTIFY isAnimationAllowedChanged);
  Q_PROPERTY(int          numOfRows             READ getNumOfRows           WRITE setNumOfRows          NOTIFY numOfRowsChanged);
  Q_PROPERTY(int          numOfCols             READ getNumOfCols           WRITE setNumOfCols          NOTIFY numOfColsChanged);
  Q_PROPERTY(int          squareSize            READ getSquareSize          WRITE setSquareSize         NOTIFY squareSizeChanged);
  Q_PROPERTY(int          squareSpacing         READ getSquareSpacing       WRITE setSquareSpacing      NOTIFY squareSpacingChanged);
  Q_PROPERTY(int          timerPeriod           READ getTimerPeriod         WRITE setTimerPeriod        NOTIFY timerPeriodChanged);
  Q_PROPERTY(int          currentPatternIndex   READ getPatternIndex        WRITE setCurrentPattern     NOTIFY patternIndexChanged);
  Q_PROPERTY(int          minNumOfRowsAndCols   READ getMinNumOfRowsAndCols CONSTANT);
  Q_PROPERTY(int          maxNumOfRowsAndCols   READ getMaxNumOfRowsAndCols CONSTANT);
  Q_PROPERTY(int          minTimerPeriod_ms     READ getMinTimerPeriod_ms   CONSTANT);
  Q_PROPERTY(int          maxTimerPeriod_ms     READ getMaxTimerPeriod_ms   CONSTANT);
  Q_PROPERTY(int          minSquareSize         READ getMinSquareSize       CONSTANT);
  Q_PROPERTY(int          maxSquareSize         READ getMaxSquareSize       CONSTANT);
  Q_PROPERTY(int          minSquareSpacing      READ getMinSquareSpacing    CONSTANT);
  Q_PROPERTY(int          maxSquareSpacing      READ getMaxSquareSpacing    CONSTANT);
  Q_PROPERTY(QStringList  listOfPatterns        READ getListOfPatterns      CONSTANT);

  Q_INVOKABLE void              clearBoard            (void);
  Q_INVOKABLE void              recalculateBoard      (void);
  Q_INVOKABLE int               getNumOfRows          (void)          const;
  Q_INVOKABLE int               getNumOfCols          (void)          const;
  Q_INVOKABLE int               getTimerPeriod        (void)          const;
  Q_INVOKABLE int               getSquareSize         (void)          const;
  Q_INVOKABLE int               getSquareSpacing      (void)          const;
  Q_INVOKABLE bool              getIsAnimationAllowed (void)          const;
  Q_INVOKABLE bool              getCellStatus         (int cellIndex) const;
  Q_INVOKABLE const QStringList getListOfPatterns     (void)          const;
  Q_INVOKABLE int               getPatternIndex       (void)          const;
  Q_INVOKABLE int               getMinNumOfRowsAndCols(void)          const;
  Q_INVOKABLE int               getMaxNumOfRowsAndCols(void)          const;
  Q_INVOKABLE int               getMinTimerPeriod_ms  (void)          const;
  Q_INVOKABLE int               getMaxTimerPeriod_ms  (void)          const;
  Q_INVOKABLE int               getMinSquareSize      (void)          const;
  Q_INVOKABLE int               getMaxSquareSize      (void)          const;
  Q_INVOKABLE int               getMinSquareSpacing   (void)          const;
  Q_INVOKABLE int               getMaxSquareSpacing   (void)          const;
  Q_INVOKABLE void              setNumOfRows          (int numOfRows);
  Q_INVOKABLE void              setNumOfCols          (int numOfCols);
  Q_INVOKABLE void              setSquareSize         (int squareSize);
  Q_INVOKABLE void              setSquareSpacing      (int squareSpacing);
  Q_INVOKABLE void              setTimerPeriod        (int timerPeriod_ms);
  Q_INVOKABLE void              setIsAnimationAllowed (bool isAnimationAllowed);
  Q_INVOKABLE void              setCurrentPattern     (int patternIndex);
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
  void patternIndexChanged        (int);

private:

  QScopedPointer<GameOptions> m_gameOptions;
  QScopedPointer<GameBoard>   m_gameBoard;
  QScopedPointer<Patterns>    m_patterns;
  bool m_isAnimationAllowed;

  void resizeGameBoard(void);
};

#endif // GAMEMANAGER_H
