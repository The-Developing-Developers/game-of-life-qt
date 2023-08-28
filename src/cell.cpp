#include <QDebug>
#include "cell.hpp"

Cell::Cell(void)
  : m_IsAlive(false)
{;}


void Cell::revive(void)
{
  m_IsAlive = true;
}


void Cell::kill(void)
{
  m_IsAlive = false;
}


bool Cell::isAlive(void)
{
  return m_IsAlive;
}