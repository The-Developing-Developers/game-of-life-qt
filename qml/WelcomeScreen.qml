import QtQuick
import QtQuick.Controls

Rectangle
{
  id: welcomeScreen_root

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
      horizontalCenter: welcomeScreen_root.horizontalCenter
      top: welcomeScreen_root.top
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
    id: optionsBackground

    readonly property int someHeightMargin: 70
    readonly property int someWidthMargin:  20
    readonly property int applicationWindowMinimumWidth: 800

    height: optionsText.height + gameOptions.height + someHeightMargin
    width:  applicationWindowMinimumWidth - someWidthMargin
    radius: 10
    color: "#DDDDDD"
    border.color: "black"

    anchors
    {
      horizontalCenter: welcomeScreen_root.horizontalCenter
      top: introText.bottom
      topMargin: 50
    }
  }

  Text
  {
    id: optionsText

    anchors
    {
      horizontalCenter: optionsBackground.horizontalCenter
      top: optionsBackground.top
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
      horizontalCenter: optionsBackground.horizontalCenter
      top:              optionsText.bottom
      topMargin: 10
    }
  }

  Row
  {
    id: startAndQuitButtons

    anchors
    {
      horizontalCenter: welcomeScreen_root.horizontalCenter
      top:              optionsBackground.bottom
      topMargin: 50
    }

    property int someMargin: 100

    spacing: optionsBackground.width - startButton.width - quitButton.width - someMargin

    CustomButton
    {
      id: startButton

      padding:      20
      pixelSize_a:  30
      text_a:       "Start Game of Life"

      onClicked: main_root.isGameActive = true
    }

    CustomButton
    {
      id: quitButton

      width: startButton.width

      padding:      20
      pixelSize_a:  30
      text_a:       "Quit"

      pushedColour_a: "#FFAA00"
      hoverColour_a:  "red"
      normalColour_a: "#803030"

      onClicked: Qt.quit();
    }
  } // id: startAndQuitButtons
}