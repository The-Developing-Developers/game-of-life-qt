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

  ScrollView
  {
    id: scrollView

    anchors
    {
      top:    root.top
      left:   root.left
      right:  root.right
      bottom: buttons.top
      leftMargin:   50
      rightMargin:  50
      bottomMargin: 20
    }

    contentWidth:  squareSpacing + (squareSide + squareSpacing) * cols
    contentHeight: squareSpacing + (squareSide + squareSpacing) * rows

    onWidthChanged: function() { gridBackground.adjustGridPositioning(); }

    Rectangle
    {
      id: gridBackground

      width:  scrollView.contentWidth
      height: scrollView.contentHeight
      color: "lightGrey"
      border.width: 2

      MouseArea
      {
        id: backMouseArea

        anchors.fill: gridBackground
        preventStealing: true
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

      function adjustGridPositioning()
      {
        if (gridBackground.width < scrollView.width)
          gridBackground.x = (scrollView.width - gridBackground.width) / 2;
        else
          gridBackground.x = 0;
      }
    } // id: gridBackground

    Grid
    {
      id: gameBoard

      anchors
      {
        fill:       gridBackground
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

          property bool isAlive: backend.getCellStatus(index)

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
    } // id: gameBoard
  } // id: scrollView

  Rectangle
  {
    id: buttonsBackground

    anchors.fill: buttons
    anchors.margins: -10

    border.color: "#00578a"
    border.width: 2
    color: "slateGrey"
    radius: 10
  }

  Column
  {
    id: buttons

    anchors.horizontalCenter: scrollView.horizontalCenter
    anchors.bottom: root.bottom
    anchors.bottomMargin: 20

    spacing: 20

    CustomButton
    {
      id: startGameButton

      anchors.horizontalCenter: buttons.horizontalCenter

      width:        200
      pixelSize_a:  30
      text_a:       "Start Game"

      pushedColour_a: "#00FF00"
      hoverColour_a:  "#00AF00"
      normalColour_a: "#007F00"
      normalTextColour_a: "white"
      hoverTextColour_a:  "white"

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
    } // id: startGameButton

    Row
    {
      id: otherButtons

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
  } // Column

  Timer
  {
    id: timer

    interval: backend.getTimerPeriod();
    running:  false;
    repeat:   true
    onTriggered: function() { backend.recalculateBoard(); }
  }
} // id: root