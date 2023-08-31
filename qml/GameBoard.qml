import QtQuick
import QtQuick.Controls
import GameStateEnum

Item
{
  id: root

  anchors.fill: parent

  property int squareSpacing: backend.getSquareSpacing()
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

    MouseArea
    {
      id: backMouseArea

      anchors.fill: background
      acceptedButtons: Qt.LeftButton | Qt.RightButton

      onPressed: function(mouse)
      {
        if (timer.running === false)
          backend.backgroundInteracted(mouse.x, mouse.y) // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user
      }

      onPositionChanged: function(mouse)
      {
        if (timer.running === false)
          backend.backgroundInteracted(mouse.x, mouse.y) // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user
      }

      onReleased: function()
      {
        if (timer.running === false)
          backend.backgroundReleased() // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user
      }
    }
  }

  Grid
  {
    anchors
    {
      fill:       background
      topMargin:  squareSpacing
      leftMargin: squareSpacing
    }

    spacing: squareSpacing
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
          function onBoardRecalculated()  { cell.isAlive = backend.getCellStatus(index); }
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

  CustomButton
  {
    id: startGameButton

    anchors
    {
      horizontalCenter: background.horizontalCenter
      top:              background.bottom
      topMargin:        50
    }

    width:        250
    pixelSize_a:  30
    text_a:       "Start Game"

    pushedColour_a: "#00FF00"
    hoverColour_a:  "#00AF00"
    normalColour_a: "#007F00"
    normalTextColour_a: "white"
    hoverTextColour_a: "white"

    onClicked: function()
    {
      if ( timer.running )
      {
        timer.running = false;
        text_a = "Click to restart";
      }
      else
      {
        timer.running = true
        text_a = "Click to stop";
      }
    }
  }

  Row
  {
    id: otherButtons

    anchors
    {
      horizontalCenter: startGameButton.horizontalCenter
      top:              startGameButton.bottom
      topMargin:        50
    }

    spacing: 100

    CustomButton
    {
      id: clearBoardButton

      width:        250
      pixelSize_a:  24
      text_a: "Clear Game Board"
      enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user

      onClicked: function() { backend.clearBoard(); }
    }

    CustomButton
    {
      id: backToOptionsButton

      width:        250
      pixelSize_a:  24
      text_a: "Go back to options"
      enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user

      onClicked: function()
      {
        backend.changeGameState(GameState.WelcomeScreen);
      }
    }
  } // Row

  // TODO: bad. The front-end should know nothing about board initialisation in the back-end
  Component.onCompleted:
  {
    backend.initialiseBoard();
  }
} // Item