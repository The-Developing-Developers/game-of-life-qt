import QtQuick
import QtQuick.Controls
import QtQml.Models
import GameStateEnum

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
          onClicked: main_root.isGameActive = false
        }
      }
    } // Row

    ComboBox
    {
      onActivated:
      {
        if (currentValue == "Block")
        {
          gameManager.numOfRows = 4;
          gameManager.numOfCols = 4;
        }
        else if (currentValue == "Bee-Hive")
        {
          gameManager.numOfRows = 5;
          gameManager.numOfCols = 6;
        }
        else if (currentValue == "Loaf" || currentValue == "Toad" || currentValue == "Beacon")
        {
          gameManager.numOfRows = 6;
          gameManager.numOfCols = 6;
        }
        else if (currentValue == "Boat" || currentValue == "Tub" || currentValue == "Blinker")
        {
          gameManager.numOfRows = 5;
          gameManager.numOfCols = 5;
        }
        else if (currentValue == "Pulsar")
        {
          gameManager.numOfRows = 17;
          gameManager.numOfCols = 17;
        }
        else if (currentValue == "Penta-decathlon")
        {
          gameManager.numOfRows = 11;
          gameManager.numOfCols = 18;
        }
        else if (currentValue == "Glider")
        {
          gameManager.numOfRows = 20;
          gameManager.numOfCols = 20;
        }
        else
        {
          gameManager.numOfRows = 3;
          gameManager.numOfCols = 3;
        }
      }

      model:
      [
        "Block",
        "Bee-Hive",
        "Loaf",
        "Boat",
        "Tub",
        "Blinker",
        "Beacon",
        "Pulsar",
        "Penta-decathlon",
        "Glider"
      ]
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
} // id: gameBoard_root
