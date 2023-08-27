import QtQuick
import QtQuick.Controls

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
    font.pixelSize: 50
    font.bold: true
    color: "black" /* "#EEEEEE" */ /* "#d3e4ed" */
  }

  GameOptions
  {
    id: gameOptions

    anchors
    {
      // fill: background
      horizontalCenter: root.horizontalCenter
      top:              introText.bottom
      topMargin: 100
    }
  }

  CustomButton
  {
    anchors
    {
      horizontalCenter: root.horizontalCenter
      top: gameOptions.bottom
      topMargin: 100
    }

    padding:  20
    fontSize: 30
    butnText: "Start Game of Life"

    onClicked: function()
    {
      root.startGame = true;
    }
  }

  Binding
  {
    target: parent
    property: "startGame" // name of parent's property
    value: root.startGame // parent's property is now bound to `root.startGame`
  }
}