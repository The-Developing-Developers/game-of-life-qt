import QtQuick
import QtQuick.Controls

ScrollView
{
  id: scrollView

  property int squareSpacing: gameManager.getSquareSpacing()
  property int squareSide:    gameManager.getSquareSize()
  property int rows:          gameManager.getNumOfRows()
  property int cols:          gameManager.getNumOfCols()
  property int numOfSquares:  rows * cols

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
          gameManager.backgroundInteracted(mouse.x, mouse.y) // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user
      }

      onPositionChanged: function(mouse)
      {
        if (timer.running === false)
          gameManager.backgroundInteracted(mouse.x, mouse.y) // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user
      }

      onReleased: function()
      {
        if (timer.running === false)
          gameManager.backgroundReleased() // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user
      }
    }

    // Centres the game board if its width is smaller than the ScrollView's width
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
      model: scrollView.numOfSquares

      Rectangle
      {
        id: cell

        property bool isAlive: gameManager.getCellStatus(index)

        width:  scrollView.squareSide
        height: scrollView.squareSide
        border.width: 1
        color: isAlive === true ? "yellow" : "black"

        Connections
        {
          target: gameManager
          function onBoardRecalculated()  { cell.isAlive = gameManager.getCellStatus(index); }
        }
      } // id: cell
    } // Repeater
  } // id: gameBoard
} // id: scrollView