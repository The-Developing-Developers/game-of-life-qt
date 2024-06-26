/**
  One of the two QML documents loaded by the `Loader`. It represents the actual game screen, where the users can interact with the game board.
*/

import QtQuick
import QtQuick.Controls

Item
{
  id: gameBoard_root

  anchors.fill: parent

  CustomScrollView // The actual game grid
  {
    id: scrollView

    anchors
    {
      top:    gameBoard_root.top
      left:   gameBoard_root.left
      right:  gameBoard_root.right
      bottom: buttons.top
      leftMargin:   50
      rightMargin:  50
      bottomMargin: 20
    }
  }

  // Buttons and game controls

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
    anchors.bottom: gameBoard_root.bottom
    anchors.bottomMargin: 20

    spacing: 20

    CustomButton
    {
      id: startGameButton

      anchors.horizontalCenter: buttons.horizontalCenter

      width:        230
      pixelSize_a:  30
      text_a:       "Start Game"

      readonly property string white:             "white"
      readonly property string normalGreen:       "#007F00"
      readonly property string pushedGreen:       "#00AF00"
      readonly property string hoverGreen:        "#00FF00"
      readonly property string normalOrange:      "#ff8800"
      readonly property string pushedOrange:      "#ffaa00"
      readonly property string hoverOrange:       "#ffcc00"

      normalColour_a:     timer.running ? normalOrange : normalGreen
      hoverColour_a:      timer.running ? pushedOrange : pushedGreen
      pushedColour_a:     timer.running ? hoverOrange  : hoverGreen
      normalTextColour_a: white
      hoverTextColour_a:  white

      onClicked:
      {
        timer.toggleTimer();
        startGameButton.changeText();
      }

      function changeText()
      {
        if ( timer.running )
          text_a = "Click to stop";
        else
          text_a = "Click to restart";
      }
    } // id: startGameButton

    Row
    {
      id: otherButtons

      spacing: 30

      CustomButton
      {
        id: clearBoardButton

        width:        230
        pixelSize_a:  24
        text_a: "Clear Game Board"
        enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user

        onClicked: function()
        {
          warningPopup.open()
        }
      }

      CustomButton
      {
        id: backToOptionsButton

        width:        230
        pixelSize_a:  24
        text_a: "Go Back To Options"
        enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user

        onClicked: function()
        {
          onClicked: main_root.isGameActive = false
        }
      }

      CustomButton
      {
        id: shapeSelectorPopupButton

        width:        230
        pixelSize_a:  24
        text_a: "Select Shape"
        enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user
        Keys.forwardTo: [shapeSelectorPopup.currentItem_a];

        onClicked: function()
        {
          shapeSelectorPopup.open()
        }
      }

    } // Row

  } // Column

  WarningPopup
  {
    id: warningPopup
  }

  ShapeSelectorPopup
  {
    id: shapeSelectorPopup
    width:  parent.width  * 0.50
    height: parent.height * 0.90
  }

  Connections
  {
    target: warningPopup

    function onYesClicked() { gameManager.clearBoard(); }  // called when "warningPopup" raises "yesClicked" signal
  }

  Connections
  {
    target: shapeSelectorPopup

    function onYesClicked() // called when "shapeSelectorPopup" raises "yesClicked" signal
    {
      gameManager.currentPatternIndex = shapeSelectorPopup.currentIndex_a

      // Forces the `Loader` in `main_root` to reload the `gameScreen`, to redraw the `GameBoard` and make it centered in its parent object
      main_root.resetGameBoard = true;
      main_root.resetGameBoard = false;
    }
  }

  // Game timer: when it expires, the game board is recalculated, beacuse a new cycle of the Game of Life begins. It can be started and
  // stopped by external factors, by using the dedicated `toggleTimer` function.
  Timer
  {
    id: timer

    interval: gameManager.timerPeriod;
    running:  false;
    repeat:   true
    onTriggered: function() { gameManager.recalculateBoard(); }

    function toggleTimer()
    {
      if ( timer.running )
        timer.running = false;
      else
        timer.running = true
    }
  }

  Connections
  {
    target: gameManager

    function onStopTimer()
    {
      timer.running = false
      startGameButton.changeText();
    }
  }
} // id: gameBoard_root
