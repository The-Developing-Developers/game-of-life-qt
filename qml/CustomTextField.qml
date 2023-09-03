import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

TextField
{
  width:  160
  height: 50

  focus: true
  font.pointSize: 14
  wrapMode: TextInput.Wrap

  background: Rectangle
  {
    radius: 5
    color:        parent.enabled      ? "lightGrey"   : "#353637"
    border.color: parent.activeFocus  ? "teal"        : "black"
    border.width: parent.activeFocus  ? 3 : 1
  }
}