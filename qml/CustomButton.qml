import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Button
{
  id: customButton

  property alias fontSize: theText.font.pixelSize
  property alias butnText: theText.text

  background: Rectangle
  {
    property string pushedColour: "#bbbbbb"
    property string  hoverColour: "#3275a8"
    property string normalColour: "#8bb0cc"

    color: customButton.down ? pushedColour : (customButton.hovered ? hoverColour : normalColour)

    border.width: 1
    border.color: "#414f45"

    radius: 5
  }

  contentItem: Text
  {
    id: theText

    text: "Text here..."
    font.pixelSize: 12
    opacity: enabled ? 1.0 : 0.3
    color: customButton.hovered ? "white" : "black"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment:   Text.AlignVCenter
    elide: Text.ElideRight
  }
}