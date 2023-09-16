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
  padding:  0

  Overlay.modal: Rectangle
  {
    // color: "#aacfdbe7"
    color: "#AAAAAAAA" // Background is greyed out when Popup is active
  }

  signal yesClicked()

  contentItem: Rectangle
  {
    id: rect

    color: "yellow"
    border.color: "blue"
    border.width: 5
    radius: 5

    Column
    {
      id: background

      anchors.centerIn: rect
      spacing: 20

      Text
      {
        anchors.horizontalCenter: background.horizontalCenter
        text: "Are you sure?"
        color: "blue"
        font.pixelSize: 30
      }

      Row
      {
        id: yesNoButtons

        anchors.horizontalCenter: background.horizontalCenter
        spacing: 20

        CustomButton
        {
          id: yesButton

          width:        100
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

          width:        100
          pixelSize_a:  24
          text_a: "No"

          onClicked: function()
          {
            popup.close()
          }
        }
      } // id: yesNoButtons
    } // id: background
  } // id: rect
} // id: popup