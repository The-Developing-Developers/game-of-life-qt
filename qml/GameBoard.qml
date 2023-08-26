import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Item
{
  id: root

  anchors.fill: parent

  property int squareSide:    50
  property int squareSpacing: 5
  property int rows: 10 // TODO: ask the user, avoid hard-coding
  property int cols: 15 // TODO: ask the user, avoid hard-coding
  property int numOfSquares:  rows * cols

  Rectangle
  {
    id: rootRect

    anchors.horizontalCenter: root.horizontalCenter

    width:  (squareSide + squareSpacing) * cols + squareSpacing
    height: (squareSide + squareSpacing) * rows + squareSpacing
    border.width: 1
  }

  Grid
  {
    id: gameBoard

    anchors
    {
      fill: rootRect
      topMargin: squareSpacing
      leftMargin: squareSpacing
    }

    spacing: squareSpacing
    // columns: Math.floor(root.width / (root.squareSide + root.squareSpacing)) // resizes dynamically. Undesirable
    columns: cols // size of game board does not vary when resizing the ApplicationWindow

    Repeater
    {
      id: repeater

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
          function onBoardRecalculated()
          {
            isAlive = backend.getCellStatus(index);
            console.log("Board has been updated. Cell " + index + " is: " + isAlive);
          }
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
    } // id: repeater
  } // id: gameBoard

  Timer
  {
    id: timer

    interval: 1000;
    running: false;
    repeat:  true
    onTriggered: function()
    {
      console.log("Timer expired. Recalculating board...");
      backend.recalculateBoard();
    }
  }

  CustomButton
  {
    id: startGameButton

    fontSize: 20
    butnText: "Start Game"

    anchors
    {
      horizontalCenter: rootRect.horizontalCenter
      top:              rootRect.bottom
      topMargin:        50
    }

    onClicked: function()
    {
      if ( timer.running === true )
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

    fontSize: 20
    butnText: "Clear Game Board"

    anchors
    {
      horizontalCenter: rootRect.horizontalCenter
      top:              startGameButton.bottom
      topMargin:        20
    }

    onClicked: function()
    {

      if ( timer.running === true )
      {
        // Do nothing
      }
      else
      {
        console.log("Clearing board... (NOT YET IMPLEMENTED)") // TODO: implement!
      }
    }
  }

  Component.onCompleted:
  {
    backend.initialiseGrid(root.rows, root.cols);
  }
} // Item