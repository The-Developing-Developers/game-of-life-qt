import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Button
{
  id: customButton

  property alias pixelSize_a:         theText.font.pixelSize
  property alias pointSize_a:         theText.font.pointSize
  property alias text_a:              theText.text
  property alias normalTextColour_a:  theText.normalTextColour
  property alias hoverTextColour_a:   theText.hoverTextColour
  property alias pushedColour_a:      backgroundRect.pushedColour
  property alias hoverColour_a:       backgroundRect.hoverColour
  property alias normalColour_a:      backgroundRect.normalColour

  background: Rectangle
  {
    id: backgroundRect

    property string pushedColour: "#bbbbbb"
    property string hoverColour:  "#8bb0cc"
    property string normalColour: "#3275a8"

    color: customButton.down ? pushedColour : (customButton.hovered ? hoverColour : normalColour)

    border.width: 1
    border.color: "#414f45"

    radius: 5
  }

  contentItem: Text
  {
    id: theText

    property string normalTextColour: "white"
    property string hoverTextColour:  "black"

    text: "Text here..."
    opacity: enabled ? 1.0 : 0.3
    color: customButton.hovered ? hoverTextColour : normalTextColour
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment:   Text.AlignVCenter
    elide: Text.ElideRight
  }
}