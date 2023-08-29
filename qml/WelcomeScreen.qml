import QtQuick
import QtQuick.Controls
import GameStateEnum

Rectangle
{
  id: root

  property bool startGame: false
  anchors.centerIn: parent
  gradient: Gradient
  {
    GradientStop { position: 0.0; color: "lightGrey" }
    GradientStop { position: 0.5; color: "slateGrey" }
    GradientStop { position: 1.0; color: "black" }
  }

  Text
  {
    id: introText

    anchors
    {
      horizontalCenter: root.horizontalCenter
      top: root.top
      topMargin: 20
    }

    text: "John Conway's Game of Life"
    font.family: "Georgia"
    font.pixelSize: 50
    font.bold: true
    color: "#205050"
  }

  Rectangle
  {
    id: optionsRect

    color: "#DDDDDD"
    height: 200
    width:  1200
    radius: 10

    anchors
    {
      horizontalCenter: root.horizontalCenter
      top: introText.bottom
      topMargin: 180
    }

    Text
    {
      id: optionsText

      anchors
      {
        horizontalCenter: optionsRect.horizontalCenter
        top: optionsRect.top
        topMargin: 20
      }

      text: "Set up the game options:"
      font.family: "Helvetica"
      font.pixelSize: 32
      font.bold: true
      color: "black"
    }

    GameOptions
    {
      id: gameOptions

      anchors
      {
        horizontalCenter: optionsRect.horizontalCenter
        top:              optionsText.bottom
        topMargin: 50
      }
    }
  } // id: optionsRect

  CustomButton
  {
    id: startButton

    anchors
    {
      horizontalCenter: root.horizontalCenter
      top:              optionsRect.bottom
      topMargin: 130
    }

    padding:      20
    pixelSize_a:  30
    text_a:       "Start Game of Life"

    onClicked: backend.changeGameState(GameState.GameBoard)
  }

  CustomButton
  {
    id: quitButton

    anchors
    {
      horizontalCenter: startButton.horizontalCenter
      top:              startButton.bottom
      topMargin: 50
    }

    padding:      20
    pixelSize_a:  20
    text_a:       "Quit"

    pushedColour_a: "#FFAA00"
    hoverColour_a:  "red"
    normalColour_a: "#803030"

    onClicked: Qt.quit();
  }
}