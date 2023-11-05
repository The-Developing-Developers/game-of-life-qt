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

  placeholderTextColor: "grey"
  color: "black"

  property bool acceptableInputOrEmpty: acceptableInput || !text

  background: Rectangle
  {
    radius: 5
    color:
    {
      if (parent.activeFocus)
      {
        if(acceptableInputOrEmpty)
        {
          return "white";
        }
      }
      else
      {
        if(acceptableInputOrEmpty)
        {
          return "lightgrey";
        }
      }

      return "red";
    }

    border.color: parent.activeFocus  ? "teal"  : "black"
    border.width: parent.activeFocus  ? 3 : 1
  }
}
