import QtQuick
import QtQuick.Controls

Rectangle
{
  id: cell

  border.width: 1
  property bool isAlive: {isAlive = gameManager.getCellStatus(index)}
  color: {color = isAlive === true ? aliveColour : deadColour} // Assignation without binding. Useful for ColorAnimation

  readonly property double aliveDurationFactor: 0.75 // Arbitrarily chosen
  readonly property double  deadDurationFactor: 0.25 // Arbitrarily chosen
  readonly property string aliveColour: "yellow"
  readonly property string  deadColour: "black"

  ColorAnimation
  {
    id: animationCellAlive;

    target:         cell;
    alwaysRunToEnd: true;
    property:       "color";
    to:             aliveColour;
    duration:       gameManager.getTimerPeriod() * aliveDurationFactor
  }

  ColorAnimation
  {
    id: animationCellDead;

    target:         cell;
    alwaysRunToEnd: true;
    property:       "color";
    to:             deadColour;
    duration:       gameManager.getTimerPeriod() * deadDurationFactor
  }

  Connections
  {
    target: gameManager
    function onBoardChanged()
    {
      changeCellColour()
    }
  }

  function changeCellColour()
  {
    cell.isAlive = gameManager.getCellStatus(index);

    if (cell.isAlive)
    {
      if (gameManager.isGameTimerRunning())
        animationCellAlive.restart(); // Use the animation only when the game is running
      else
        cell.color = aliveColour
    }
    else
    {
      if (gameManager.isGameTimerRunning())
        animationCellDead.restart(); // Use the animation only when the game is running
      else
        cell.color = deadColour
    }

  }
} // id: cell