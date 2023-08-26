#include <QDebug>
#include "cell.hpp"

Cell::Cell(void)
  : m_IsAlive(false)
  // : m_IsAlive(true)
{
  // qDebug() << __func__ << ": Live cell created.";
  // qDebug() << __func__ << ": Dead cell created.";
}


void Cell::revive(void)
{
  m_IsAlive = true;
  qDebug() << __func__ << ": Cell revived.";
}


void Cell::kill(void)
{
  m_IsAlive = false;
  qDebug() << __func__ << ": Cell killed.";
}


bool Cell::isAlive(void)
{
  return m_IsAlive;
}