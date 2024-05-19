/**
  Instantiated by the `CustomScrollView`. It graphically represents an individual cell in the game grid. Uses `ColorAnimation`s to animate
  the transition between the "dead" colour and the "alive" colour.
*/

import QtQuick
import QtQuick.Controls

Rectangle
{
  id: cell

  border.width: 1
  property bool isAlive: {isAlive = gameManager.getCellStatus(index)}
  color: {color = isAlive === true ? aliveColour : deadColour} // Assignation without binding. Useful for `ColorAnimation`

  readonly property double aliveDurationFactor: 0.25 // Arbitrarily chosen
  readonly property double  deadDurationFactor: 0.75 // Arbitrarily chosen
  readonly property string aliveColour: "yellow"
  readonly property string  deadColour: "black"

  ColorAnimation
  {
    id: animationCellAlive;

    target:         cell;
    alwaysRunToEnd: true;
    property:       "color";
    to:             aliveColour;
    duration:       gameManager.timerPeriod * aliveDurationFactor
  }

  ColorAnimation
  {
    id: animationCellDead;

    target:         cell;
    alwaysRunToEnd: true;
    property:       "color";
    to:             deadColour;
    duration:       gameManager.timerPeriod * deadDurationFactor
  }

  Connections
  {
    target: gameManager

    function onBoardChanged() // This slot reacts to the `boardChanged` signal raised by the `gameManager`.
    {
      changeCellColour()
    }
  }

  function changeCellColour()
  {
    cell.isAlive = gameManager.getCellStatus(index);

    if (cell.isAlive)
    {
      if (timer.running && gameManager.isAnimationAllowed) // TODO: encapsulate `timer.running` into a boolean value for ease of use?
        animationCellAlive.restart(); // Use the animation only when the game is running
      else
        cell.color = aliveColour
    }
    else
    {
      if (timer.running && gameManager.isAnimationAllowed) // TODO: encapsulate `timer.running` into a boolean value for ease of use?
        animationCellDead.restart(); // Use the animation only when the game is running
      else
        cell.color = deadColour
    }
  }

} // id: cell