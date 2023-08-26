#include <QDebug>
#include "cell.hpp"

#define NDEBUG

Cell::Cell(void)
  : m_IsAlive(false)
  // : m_IsAlive(true)
{
  // qDebug() << "Live cell created.";
  // qDebug() << "Dead cell created.";
}


void Cell::Revive(void)
{
  m_IsAlive = true;
  qDebug() << "Cell revived.";
}


void Cell::Kill(void)
{
  m_IsAlive = false;
  qDebug() << "Cell killed.";
}


bool Cell::IsAlive(void)
{
  return m_IsAlive;
}