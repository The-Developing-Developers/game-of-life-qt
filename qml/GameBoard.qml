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
  property int startButtonHeight: 20
  property int startButtonMargins: 10

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

  // TODO: rimpiazzare con un CustomButton e rimuovere StartButton.qml
  StartButton
  {
    id: startButton

    fontSize: 20

    anchors
    {
      horizontalCenter: rootRect.horizontalCenter
      top:              rootRect.bottom
      topMargin:        rootRect.startButtonMargins
    }

    onClicked: function()
    {
      if ( timer.running === true )
      {
        timer.running = false
        console.log("Timer stopped");
      }
      else
      {
        timer.running = true
        console.log("Timer is running");
      }
    }
  }

  Component.onCompleted:
  {
    backend.initialiseGrid(root.rows, root.cols);
  }
} // Item