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
    id: popupContent

    color: "red"
    border.color: "blue"
    border.width: 5
    radius: 5

    Column
    {
      id: background

      anchors.centerIn: popupContent
      spacing: 20

      ListView
      {
        id: list
        width:  600
        height: 600
        spacing: 5

        Component // It is used to represent every single element of the ListView: it is used as the delegate of the ListView
        {
          id: availableShapes

          Rectangle
          {
            id: wrapper
            anchors.horizontalCenter: parent.horizontalCenter
            width: ListView.view.width - (popupContent.border.width * 2) // 'ListView.view.width' (instead of 'list.width') is always safe to use within a delegate, because it always refers to the 'ListView' that the delegate is currently attached to.
            height: shapeName_string.height
            color: ListView.isCurrentItem ? "yellow" : "red"

            Text // Formats the text from `ShapesModel.qml`
            {
              id: shapeName_string
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
        delegate: availableShapes
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
  } // id: popupContent
} // id: popup