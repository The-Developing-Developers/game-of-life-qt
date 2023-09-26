import QtQuick
import QtQuick.Controls
import GameStateEnum

Item
{
  id: root

  anchors.fill: parent

  CustomScrollView
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

      normalColour_a:     timer.running? "#ff8800" : "#007F00"
      hoverColour_a:      timer.running? "#ffaa00" : "#00AF00"
      pushedColour_a:     timer.running? "#ffcc00" : "#00FF00"
      normalTextColour_a: "white"
      hoverTextColour_a:  "white"

      onClicked: toggleTimerAndChangeText()

      function toggleTimerAndChangeText()
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

      spacing: 100

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
        text_a: "Go back to options"
        enabled: timer.running ? false : true // When the game has started (i.e., the timer is running), the cells are no longer modifiable by the user

        onClicked: function()
        {
          gameManager.changeGameState(GameState.WelcomeScreen);
        }
      }
    } // Row
  } // Column

  WarningPopup
  {
    id: popup
  }

  Connections
  {
    target: popup

    function onYesClicked() { gameManager.clearBoard(); }
  }

  Timer
  {
    id: timer

    interval: gameManager.getTimerPeriod();
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
} // id: root
