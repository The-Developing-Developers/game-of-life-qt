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
    color: "black"
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
      topMargin: 200
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
    anchors
    {
      horizontalCenter: root.horizontalCenter
      top: optionsRect.bottom
      topMargin: 150
    }

    padding:  20
    fontSize: 30
    butnText: "Start Game of Life"

    onClicked: backend.changeGameState(GameState.GameBoard)
  }
}