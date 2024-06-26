/**
  Instantiated by the `GameBoard`. It is a personalised `ScrollView` used to represent the actual game grid.
*/

import QtQuick
import QtQuick.Controls

ScrollView
{
  id: scrollView

  property int squareSpacing: gameManager.squareSpacing
  property int squareSide:    gameManager.squareSize
  property int numOfSquares:  gameManager.numOfRows * gameManager.numOfCols

  contentWidth:  squareSpacing + (squareSide + squareSpacing) * gameManager.numOfCols
  contentHeight: squareSpacing + (squareSide + squareSpacing) * gameManager.numOfRows

  onWidthChanged: function() { gridBackground.adjustGridPositioning(); }

  Rectangle
  {
    id: gridBackground

    width:  scrollView.contentWidth
    height: scrollView.contentHeight
    color: "lightGrey"
    border.width: 2

    // The mouse area fills the whole game grid instead of being defined for each single cell. This allows the user to click and drag the
    // mouse to quickly and conveniently toggle multiple cells with a single mouse action (see `GameManager::backgroundInteracted`).
    MouseArea
    {
      id: backMouseArea

      anchors.fill: gridBackground
      preventStealing: true
      acceptedButtons: Qt.LeftButton | Qt.RightButton

      onPressed: function(mouse)
      {
        if (! timer.running)
          gameManager.backgroundInteracted(mouse.x, mouse.y) // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user
      }

      onPositionChanged: function(mouse)
      {
        if (! timer.running)
          gameManager.backgroundInteracted(mouse.x, mouse.y) // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user
      }

      onReleased: function()
      {
        if (! timer.running)
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
    columns: gameManager.numOfCols // size of game board does not vary when resizing the ApplicationWindow

    Repeater
    {
      model: scrollView.numOfSquares

      GameCell // TODO: use the `delegate` keyword here for clarity's sake
      {
        width:  scrollView.squareSide
        height: scrollView.squareSide
      }
    }
  }
} // id: scrollView
