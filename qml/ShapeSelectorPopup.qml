import QtQuick
import QtQuick.Controls

/**
  @brief Opened in-game, when the user wants to pick a shape from the shapes library.
  Contains: \n
    - a 'ListView' \n
    - a 'Text' \n
    - a 'Row' with two 'CustomButton's \n
*/
Popup
{
  id: shapeSelectorPopup

  anchors.centerIn: Overlay.overlay // the 'Popup' is being centered within this overlay layer, ensuring it appears in the center of the overlay, above other content.
  implicitWidth:  600
  implicitHeight: 800
  modal: true // when a "Popup" or "Dialog" is modal, it prevents mouse and keyboard interaction with other elements until the "Popup" is closed.
  // focus: true
  closePolicy: Popup.NoAutoClose // The "Popup" cannot be automatically dismissed by a user action. The "Popup" will stay open until it is explicitly closed by calling the "close()" method.
  dim: false
  padding:  0

  signal yesClicked() // Raised when the user clicks the "Yes" button in 'yesButton'

  property alias currentIndex_a: listView.currentIndex

  contentItem: Rectangle // The actual content of the Popup. It is common to use a 'Rectangle' as container visual element.
  {
    id: popupContent

    color: "red"
    border.color: "blue"
    border.width: 5
    radius: 5

    ListView
    {
      id: listView
      width:  parent.width - (popupContent.border.width * 2) // Using 'ListView.view.width' (instead of 'listView.width') is always safe within a delegate, because it always refers to the 'ListView' that the delegate is currently attached to.
      height: parent.height * 0.85 // Height is slightly smaller than the parent's to accomodate for other visual elements underneath the 'listView'
      x: popupContent.border.width
      y: popupContent.border.width
      spacing: 5

      delegate: Rectangle // It is used to represent every single element of the ListView
      {
        id: wrapper
        anchors.horizontalCenter: parent.horizontalCenter
        width: ListView.view.width
        height: shapeName_string.height
        color: ListView.isCurrentItem ? "yellow" : "red"
        focus: true

        Text // Formats the text from `ShapesModel.qml`
        {
          id: shapeName_string
          text: model.name
          color: wrapper.ListView.isCurrentItem ? "red" : "white" // This line is accessing the "isCurrentItem" property of the "ListView" attached to the "wrapper" delegate (i.e., the "isCurrentItem" attached property that the ListView has provided to the "wrapper" delegate).
          font.pointSize: 20
        }

        MouseArea // The delegate is selectable with a mouse click
        {
          anchors.fill: parent
          onClicked: listView.currentIndex = index
        }
      }

      // model: gameManager.listOfPatterns; // TODO: trying to use the list defined in C++ returns an error
      model: ShapesModel {} // Loads `ShapesModel.qml` (data container)
    }

    Text
    {
      id: selectShape_text
      anchors.top: listView.bottom
      anchors.horizontalCenter: parent.horizontalCenter
      text: "Select Shape?"
      color: "blue"
      font.pixelSize: 32
    }

    Row
    {
      id: yesNoButtons_row
      anchors.top: selectShape_text.bottom
      anchors.horizontalCenter: parent.horizontalCenter
      spacing: 20

      CustomButton
      {
        id: yesButton
        width:        100
        pixelSize_a:  24
        text_a: "Yes"

        onClicked: function()
        {
          shapeSelectorPopup.yesClicked();
          shapeSelectorPopup.close()
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
          shapeSelectorPopup.close()
        }
      }
    } // id: yesNoButtons_row
  } // id: popupContent
} // id: shapeSelectorPopup