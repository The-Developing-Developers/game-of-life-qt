import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

ApplicationWindow
{
  id: root

  property int startButtonHeight:   20
  property int startButtonMargins:  5
  property int squareSide:    50
  property int squareSpacing: 5
  property int rows:  5   // TODO: ask the user, avoid hard-coding
  property int cols:  10  // TODO: ask the user, avoid hard-coding
  property int numOfSquares:  rows * cols

  minimumWidth:  (squareSide + squareSpacing) * cols + squareSpacing
  minimumHeight: (squareSide + squareSpacing) * rows + squareSpacing + startButtonHeight + 2 * startButtonMargins
  visible: true
  title: qsTr("Game Of Life")

  Grid
  {
    id: grid

    x: squareSpacing; y: squareSpacing
    spacing: root.squareSpacing
    // columns: Math.floor(root.width / (root.squareSide + root.squareSpacing)) // resizes dynamically. Undesirable
    columns: root.cols // size of grid does not vary when resizing the ApplicationWindow

    Repeater
    {
      id: repeater

      model: numOfSquares

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
      } // Rectangle
    } // Repeater
  } // Grid

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

  StartButton
  {
    id: startButton

    fontSize: 20

    anchors
    {
      horizontalCenter: parent.horizontalCenter
      top:              grid.bottom
      bottom:           root.contentItem.bottom
      topMargin:        root.startButtonMargins
      bottomMargin:     root.startButtonMargins
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
  } // StartButton

  Component.onCompleted:
  {
    backend.initialiseGrid(root.rows, root.cols);
  }
}