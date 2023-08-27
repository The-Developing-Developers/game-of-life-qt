import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

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

  Row
  {
    id: gameOptions

    anchors
    {
      // fill: background
      horizontalCenter: root.horizontalCenter
      top: introText.bottom
      topMargin: 100
    }

    spacing: 20

    TextField
    {
      width:  220
      height: 50

      // focus: true
      placeholderText: "Select num. of rows"
      font.pointSize: 14
      wrapMode: TextInput.Wrap
      validator: IntValidator {bottom: 1; top: 12;}

      background: Rectangle
      {
        radius: 5
        color:        parent.enabled      ? "lightGrey"   : "#353637"
        border.color: parent.activeFocus  ? "teal"        : "transparent"
        border.width: 2
      }

      onAccepted:
      {
        // root.jsCall(input.text)
      }
    }

    TextField
    {
      width:  220
      height: 50

      // focus: true
      placeholderText: "Select num. of columns"
      font.pointSize: 14
      wrapMode: TextInput.Wrap
      validator: IntValidator {bottom: 1; top: 25;}

      background: Rectangle
      {
        radius: 5
        color:        parent.enabled      ? "lightGrey"   :  "#353637"
        border.color: parent.activeFocus  ? "teal"        : "transparent"
        border.width: 2
      }

      onAccepted:
      {
        // root.jsCall(input.text)
      }
    }

    TextField
    {
      width:  220
      height: 50

      // focus: true
      placeholderText: "Select rectangle size"
      font.pointSize: 14
      wrapMode: TextInput.Wrap
      validator: IntValidator {bottom: 10; top: 100;}

      background: Rectangle
      {
        radius: 5
        color:        parent.enabled      ? "lightGrey"   : "#353637"
        border.color: parent.activeFocus  ? "teal"        : "transparent"
        border.width: 2
      }

      onAccepted:
      {
        // root.jsCall(input.text)
      }
    }

    TextField
    {
      width:  220
      height: 50

      // focus: true
      placeholderText: "Select game speed in ms"
      font.pointSize: 14
      wrapMode: TextInput.Wrap
      validator: IntValidator {bottom: 100; top: 5000;}

      background: Rectangle
      {
        radius: 5
        color:        parent.enabled      ? "lightGrey"   : "#353637"
        border.color: parent.activeFocus  ? "teal"        : "transparent"
        border.width: 2
      }

      onAccepted:
      {
        // root.jsCall(input.text)
      }
    }
  } // Row

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