#include <QDebug>
#include "cell.hpp"

Cell::Cell(void)
{;}


void Cell::revive(void)
{
  m_isAlive = true;
}


void Cell::kill(void)
{
  m_isAlive = false;
}


void Cell::toggle(void)
{
  if (!m_isTogglingLocked)
  {
    if (m_isAlive)
      m_isAlive = false;
    else
      m_isAlive = true;
  }
}


bool Cell::isAlive(void)
{
  return m_isAlive;
}


void Cell::lockToggling(void)
{
  m_isTogglingLocked = true;
}


void Cell::unlockToggling(void)
{
  m_isTogglingLocked = false;
}