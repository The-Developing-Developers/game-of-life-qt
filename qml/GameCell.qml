import QtQuick
import QtQuick.Controls

Rectangle
{
  id: cell

  border.width: 1
  property bool isAlive: {isAlive = gameManager.getCellStatus(index)}
  color: {color = isAlive === true ? "yellow" : "black"} // Assignation without binding. Useful for ColorAnimation

  readonly property double aliveFactor: 0.25 // Arbitrarily chosen
  readonly property double  deadFactor: 0.75 // Arbitrarily chosen

  ColorAnimation
  {
    id: animationCellAlive;

    target:         cell;
    alwaysRunToEnd: true;
    property:       "color";
    to:             "yellow";
    duration:       gameManager.getTimerPeriod() * aliveFactor
  }

  ColorAnimation
  {
    id: animationCellDead;

    target:         cell;
    alwaysRunToEnd: true;
    property:       "color";
    to:             "black";
    duration:       gameManager.getTimerPeriod() * deadFactor
  }

  Connections
  {
    target: gameManager
    function onBoardChanged()
    {
      cell.isAlive = gameManager.getCellStatus(index);
      if (cell.isAlive)
        animationCellAlive.restart();
      else
        animationCellDead.restart();
    }
  }
} // id: cell