import QtQuick
import QtQuick.Controls

Item
{
  id: gameBoard_root

  anchors.fill: parent

  CustomScrollView
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

      width:        250
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

      spacing: 50

      CustomButton
      {
        id: clearBoardButton

        width:        250
        pixelSize_a:  24
        text_a: "Clear Game Board"
        enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user

        onClicked: function()
        {
          popup.open()
        }
      }

      CustomButton
      {
        id: backToOptionsButton

        width:        250
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

        width:        250
        pixelSize_a:  24
        text_a: "Select Shape"
        enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user

        onClicked: function()
        {
          shapeSelectorPopup.open()
        }
      }
    } // Row

    ComboBox
    {
      model:        gameManager.listOfPatterns;
      onActivated:  gameManager.currentPatternIndex = currentIndex
    }
  } // Column

  WarningPopup
  {
    id: popup
  }

  ShapeSelectorPopup
  {
    id: shapeSelectorPopup
  }

  Connections
  {
    target: popup

    function onYesClicked() { gameManager.clearBoard(); }
  }

  Connections
  {
    target: shapeSelectorPopup

    function onYesClicked()
    {
      gameManager.currentPatternIndex = shapeSelectorPopup.currentIndex_a
    }
  }

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
