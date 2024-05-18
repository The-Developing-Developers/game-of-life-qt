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
  closePolicy: Popup.NoAutoClose // The "Popup" cannot be automatically dismissed by a user action. The "Popup" will stay open until it is explicitly closed by calling the "close()" method.
  dim: false
  padding:  0

  signal yesClicked() // Raised when the user clicks the "Yes" button in 'yesButton'

  property alias currentIndex_a: listView.currentIndex  // Used to communicate the currently selected item in the ListView to the backend
  property alias currentItem_a:  listView.currentItem   // Used to transfer the keyboard focus from the GameBoard to the currently selected item in the ListView

  // contentItem: Rectangle // The actual content of the Popup. It is common to use a 'Rectangle' as container visual element.
  contentItem: FocusScope // TODO: try to reuse the Rectangle
  {
    id: popupContent

    width:  parent.width
    height: parent.height

    // color: "red"
    // border.color: "blue"
    // border.width: 5
    // radius: 5

    ListView
    {
      id: listView
      // width:  parent.width - (popupContent.border.width * 2) // Using 'ListView.view.width' (instead of 'listView.width') is always safe within a delegate, because it always refers to the 'ListView' that the delegate is currently attached to.
      width:  parent.width - 10 // Using 'ListView.view.width' (instead of 'listView.width') is always safe within a delegate, because it always refers to the 'ListView' that the delegate is currently attached to.
      height: parent.height * 0.85 // Height is slightly smaller than the parent's to accomodate for other visual elements underneath the 'listView'
      // x: popupContent.border.width
      x: 5
      // y: popupContent.border.width
      y: 5
      spacing: 5
      focus: true

      delegate: Rectangle // It is used to represent every single element of the ListView
      {
        id: rectangleDelegate
        anchors.horizontalCenter: parent.horizontalCenter
        width: ListView.view.width
        height: shapeName_string.height
        color: ListView.isCurrentItem ? "yellow" : "red"

        Text // Formats the text from `ShapesModel.qml`
        {
          id: shapeName_string
          text: model.name
          color: rectangleDelegate.ListView.isCurrentItem ? "red" : "white" // This line is accessing the "isCurrentItem" property of the "ListView" attached to the "rectangleDelegate" delegate (i.e., the "isCurrentItem" attached property that the ListView has provided to the "rectangleDelegate" delegate).
          font.pointSize: 20
        }

        MouseArea // The delegate is selectable with a mouse click
        {
          id: mouseArea
          anchors.fill: parent
          onClicked: listView.currentIndex = index
        }

        Keys.onReturnPressed: yesButton.clicked() // As if the "yesButton" had been clicked
        Keys.onUpPressed:     listView.decrementCurrentIndex()
				Keys.onDownPressed:   listView.incrementCurrentIndex()
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