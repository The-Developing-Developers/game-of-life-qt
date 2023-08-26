#ifndef CELL_HPP
#define CELL_HPP

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <limits>

#define NDEBUG

class Cell
{
  bool m_IsAlive;

  public:

  Cell(void);

  void Revive(void);
  void Kill(void);
  bool IsAlive(void);
};

#endif // CELL_HPP