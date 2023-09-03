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
          backend.changeGameState(GameState.WelcomeScreen);
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

    function onYesClicked() { backend.clearBoard(); }
  }

  Timer
  {
    id: timer

    interval: backend.getTimerPeriod();
    running:  false;
    repeat:   true
    onTriggered: function() { backend.recalculateBoard(); }
  }
} // id: root
