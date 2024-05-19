#ifndef GAMEOPTIONS_HPP
#define GAMEOPTIONS_HPP

class GameOptions
{
public:

   GameOptions(void);
  ~GameOptions(void);

  void  setNumOfRows                (int numOfRows);
  void  setNumOfCols                (int numOfCols);
  void  setTimerPeriod              (int timerPeriod_ms);
  void  setSquareSize               (int squareSize);
  void  setSquareSpacing            (int squareSpacing);
  int   getNumOfRows                (void) const;
  int   getNumOfCols                (void) const;
  int   getTimerPeriod              (void) const;
  int   getSquareSize               (void) const;
  int   getSquareSpacing            (void) const;
  int   getDeadOrAliveLowerThreshold(void) const;
  int   getDeadOrAliveUpperThreshold(void) const;
  int   getMinNumOfRowsAndCols      (void) const;
  int   getMaxNumOfRowsAndCols      (void) const;
  int   getMinTimerPeriod_ms        (void) const;
  int   getMaxTimerPeriod_ms        (void) const;
  int   getMinSquareSize            (void) const;
  int   getMaxSquareSize            (void) const;
  int   getMinSquareSpacing         (void) const;
  int   getMaxSquareSpacing         (void) const;

private:

  void updateNumOfRows(void);

  static constexpr int  m_minNumOfRowsAndCols       = 3;
  static constexpr int  m_maxNumOfRowsAndCols       = 50;
  static constexpr int  m_minTimerPeriod_ms         = 50;
  static constexpr int  m_maxTimerPeriod_ms         = 5000;
  static constexpr int  m_minSquareSize             = 10;
  static constexpr int  m_maxSquareSize             = 100;
  static constexpr int  m_minSquareSpacing          = 1;
  static constexpr int  m_maxSquareSpacing          = 10;
  static constexpr int  m_DeadOrAliveUpperThreshold = 3; // Game of Life's rule
  static constexpr int  m_DeadOrAliveLowerThreshold = 2; // Game of Life's rule

  int m_numOfRows       = 10;
  int m_numOfCols       = 10;
  int m_timerPeriod_ms  = 100;
  int m_squareSize      = 50;
  int m_squareSpacing   = 5;
};

#endif // GAMEOPTIONS_HPP
