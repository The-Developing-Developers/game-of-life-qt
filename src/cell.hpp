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

private:

  bool m_isAlive          = false;
  bool m_isTogglingLocked = false;
};

#endif // CELL_HPP