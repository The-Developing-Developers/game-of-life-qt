import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Rectangle
{
  id: root

  property bool startGame: false
  anchors.centerIn: parent
  color: "lightGrey"

  Text
  {
    anchors
    {
      horizontalCenter: root.horizontalCenter
      top: root.top
      topMargin: 20
    }

    text: "Press button to start Game of Life"
    font.pixelSize: 30
    font.bold: true
  }

  CustomButton
  {
    anchors
    {
      horizontalCenter: root.horizontalCenter
      verticalCenter:   root.verticalCenter
    }

    fontSize: 24
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