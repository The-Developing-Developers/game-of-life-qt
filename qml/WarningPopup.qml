/**
  Instantiated by the `GameBoard`. It is a personalised `Popup` used to warn the user that the board is going to be reset.
*/

import QtQuick
import QtQuick.Controls

Popup
{
  id: warningPopup

  anchors.centerIn: Overlay.overlay
  width:  300
  height: 300
  modal: true
  closePolicy: Popup.NoAutoClose
  padding:  0

  Overlay.modal: Rectangle
  {
    // color: "#aacfdbe7"
    color: "#AAAAAAAA" // Background is greyed out when Popup is active.
  }

  signal yesClicked() // Raised when the user clicks the "Yes" button in 'yesButton'.

  contentItem: Rectangle // The actual content of the `Popup`.
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
            warningPopup.yesClicked();
            warningPopup.close()
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
            warningPopup.close()
          }
        }

      } // id: yesNoButtons

    } // id: background

  } // id: rect

} // id: warningPopup