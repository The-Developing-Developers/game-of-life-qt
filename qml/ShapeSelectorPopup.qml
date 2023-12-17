import QtQuick
import QtQuick.Controls

Popup
{
  id: popup

  anchors.centerIn: Overlay.overlay
  width:  600
  height: 800
  modal: true
  focus: true
  closePolicy: Popup.NoAutoClose
  dim: false
  padding:  0

  signal yesClicked()

  property alias currentIndex_a: list.currentIndex

  contentItem: Rectangle
  {
    id: rect

    color: "red"
    border.color: "blue"
    border.width: 5
    radius: 5

    Column
    {
      id: background

      anchors.centerIn: rect
      spacing: 20

      ListView
      {
        id: list
        width:  600 /* rect.width */
        height: 600 /* rect.height */
        spacing: 5

        Component // Represents every single element of the ListView
        {
          id: contactsDelegate

          Rectangle
          {
            id: wrapper
            x: list.spacing // anchors here don't work
            width: rect.width - list.spacing * 2 // width is exact for centering
            height: contactInfo.height
            color: ListView.isCurrentItem ? "yellow" : "red"

            Text // Formats the text from `ShapesModel.qml`
            {
              id: contactInfo
              text: model.name
              color: wrapper.ListView.isCurrentItem ? "red" : "white"
              font.pointSize: 20
            }

            MouseArea // The element is selectable with a mouse click
            {
              anchors.fill: parent
              onClicked: list.currentIndex = index
            }
          }
        }

        // model: gameManager.listOfPatterns; // Trying to use the list defined in C++ returns an error
        model: ShapesModel {} // Loads `ShapesModel.qml` (data container)
        delegate: contactsDelegate
        focus: true
      }

      Text
      {
        anchors.horizontalCenter: background.horizontalCenter
        text: "Select Shape?"
        color: "blue"
        font.pixelSize: 32
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