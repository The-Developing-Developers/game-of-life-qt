import QtQuick
import QtQuick.Controls
import QtQml.Models
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

    ComboBox {
        textRole: "key"
        valueRole: "value"

        onActivated: gameManager.numOfRows = currentValue

        model: ListModel {
            ListElement { key: "Block"; value: 5 }
            ListElement { key: "Blinker"; value: 6 }
        }
    }
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
