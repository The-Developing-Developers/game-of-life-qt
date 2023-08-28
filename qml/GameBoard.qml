import QtQuick
import QtQuick.Controls
import GameStateEnum

Item
{
  id: root

  anchors.fill: parent

  property int squareSpacing: 5 // TODO: let the user decide
  property int squareSide:    backend.getSquareSize()
  property int rows:          backend.getNumOfRows()
  property int cols:          backend.getNumOfCols()
  property int numOfSquares:  rows * cols

  Rectangle
  {
    id: background

    anchors.horizontalCenter: root.horizontalCenter

    width:  (squareSide + squareSpacing) * cols + squareSpacing
    height: (squareSide + squareSpacing) * rows + squareSpacing
    color: "lightGrey"
    border.width: 1
  }

  Grid
  {
    anchors
    {
      fill: background
      topMargin: squareSpacing
      leftMargin: squareSpacing
    }

    spacing: squareSpacing
    // columns: Math.floor(root.width / (root.squareSide + root.squareSpacing)) // resizes dynamically. Undesirable
    columns: cols // size of game board does not vary when resizing the ApplicationWindow

    Repeater
    {
      model: root.numOfSquares

      Rectangle
      {
        id: cell

        property bool isAlive: false // All cells are dead at the creation of a new the game

        width:  root.squareSide
        height: root.squareSide
        border.width: 1
        color: isAlive === true ? "yellow" : "black"

        Connections
        {
          target: backend
          function onBoardRecalculated() { isAlive = backend.getCellStatus(index); }
        }

        MouseArea
        {
          anchors.fill: cell
          enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user

          onClicked: function()
          {
            if (isAlive)
              isAlive = false;
            else
              isAlive = true;

            backend.setCellStatus(index, isAlive);
          }
        }
      } // id: cell
    } // Repeater
  } // Grid

  Timer
  {
    id: timer

    interval: backend.getTimerPeriod();
    running: false;
    repeat:  true
    onTriggered: function() { backend.recalculateBoard(); }
  }

  Row
  {
    anchors
    {
      horizontalCenter: background.horizontalCenter
      top:              background.bottom
      topMargin:        50
    }

    spacing: 100

    CustomButton
    {
      id: startGameButton

      width: 250
      fontSize: 24
      butnText: "Start Game"

      onClicked: function()
      {
        if ( timer.running )
        {
          timer.running = false;
          butnText = "Click to restart";
        }
        else
        {
          timer.running = true
          butnText = "Click to stop";
        }
      }
    }

    CustomButton
    {
      id: clearBoardButton

      width: 250
      fontSize: 24
      butnText: "Clear Game Board"
      enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user

      onClicked: function() { backend.clearBoard(); }
    }

    CustomButton
    {
      id: backToOptionsButton

      width: 250
      fontSize: 24
      butnText: "Go back to options"
      enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user

      onClicked: function()
      {
        backend.changeGameState(GameState.WelcomeScreen);
      }
    }
  } // Row

  Component.onCompleted:
  {
    backend.initialiseBoard();
  }
} // Item