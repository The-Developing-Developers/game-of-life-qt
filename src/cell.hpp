#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
public:

  Cell(void);

  void revive         (void);
  void kill           (void);
  void toggle         (void);
  bool isAlive        (void);
  void lockToggling   (void);
  void unlockToggling (void);

  friend bool operator==(const Cell& cell_1, const Cell& cell_2);

private:

  bool m_isAlive          = false;
  bool m_isTogglingLocked = false;
};

#endif // CELL_HPP