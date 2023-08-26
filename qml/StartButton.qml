import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Button
{
  id: startButton

  property alias fontSize: theText.font.pixelSize

  background: Rectangle
  {
    property string pushedColour: "#bbbbbb"
    property string hoverColour:  "#3275a8"
    property string normalColour: "#8bb0cc"

    color: startButton.down ? pushedColour : (startButton.hovered ? hoverColour : normalColour)

    border.width: 1
    border.color: "#414f45"

    radius: 5
  }

  contentItem: Text
  {
    id: theText

    text: "Start"
    font.pixelSize: 12
    opacity: enabled ? 1.0 : 0.3
    color: startButton.hovered ? "white" : "black"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment:   Text.AlignVCenter
    elide: Text.ElideRight
  }

  // onClicked: function()
  // {
  //   if ( timer.running === true )
  //   {
  //     timer.running = false
  //     console.log("Timer stopped");
  //   }
  //   else
  //   {
  //     timer.running = true
  //     console.log("Timer is running");
  //   }
  // }
}