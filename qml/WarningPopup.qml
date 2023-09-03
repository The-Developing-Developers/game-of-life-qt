import QtQuick
import QtQuick.Controls

Popup
{
  id: popup

  anchors.centerIn: Overlay.overlay
  width:  300
  height: 300
  modal: true
  focus: true
  closePolicy: Popup.NoAutoClose
  padding: 10

  signal yesClicked()

  contentItem: Rectangle
  {
    id: rect

    color: "yellow"
    border.color: "blue"
    border.width: 5

    Column
    {
      id: background

      anchors
      {
        horizontalCenter: rect.horizontalCenter
        top: rect.top
        topMargin: 20
      }
      spacing: 20

      Text
      {
        text: "Are you sure?"
        font.pixelSize: 24
      }

      Row
      {
        id: yesNoButtons

        anchors.horizontalCenter: background.horizontalCenter
        spacing: 20

        CustomButton
        {
          id: yesButton

          width:        50
          pixelSize_a:  24
          text_a: "Yes"

          onClicked: function()
          {
            popup.yesClicked();
            popup.close()
          }
        }

        CustomButton
        {
          id: noButton

          width:        50
          pixelSize_a:  24
          text_a: "No"

          onClicked: function()
          {
            popup.close()
          }
        }
      }
    }
  }
}