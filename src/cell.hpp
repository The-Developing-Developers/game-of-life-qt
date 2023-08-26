#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
public:

  Cell(void);

  void revive(void);
  void kill(void);
  bool isAlive(void);

private:

  bool m_IsAlive;
};

#endif // CELL_HPP