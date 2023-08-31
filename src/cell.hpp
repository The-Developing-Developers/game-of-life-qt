#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
public:

  Cell(void);

  void revive (void);
  void kill   (void);
  void toggle (void);
  bool isAlive(void);

private:

  bool m_isAlive            = false;
public: // TODO: da togliere. Aggiungere setter / getter
  bool m_hasJustBeenToggled = false;
};

#endif // CELL_HPP