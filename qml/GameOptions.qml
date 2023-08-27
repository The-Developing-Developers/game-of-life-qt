import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Row
{
  spacing: 20

  TextField
  {
    width:  220
    height: 50

    // focus: true
    placeholderText: "Rows: " + backend.getNumOfRows().toString()
    font.pointSize: 14
    wrapMode: TextInput.Wrap
    validator: IntValidator {bottom: 1; top: 12;}

    background: Rectangle
    {
      radius: 5
      color:        parent.enabled      ? "lightGrey"   : "#353637"
      border.color: parent.activeFocus  ? "teal"        : "transparent"
      border.width: 2
    }

    onTextChanged:  { backend.setNumOfRows(parseInt(text)) }
    onAccepted:     { backend.setNumOfRows(parseInt(text)) }
  }

  TextField
  {
    width:  220
    height: 50

    // focus: true
    placeholderText: "Columns: " + backend.getNumOfCols().toString()
    font.pointSize: 14
    wrapMode: TextInput.Wrap
    validator: IntValidator {bottom: 1; top: 25;}

    background: Rectangle
    {
      radius: 5
      color:        parent.enabled      ? "lightGrey"   :  "#353637"
      border.color: parent.activeFocus  ? "teal"        : "transparent"
      border.width: 2
    }

    onTextChanged:  { backend.setNumOfCols(parseInt(text)) }
    onAccepted:     { backend.setNumOfCols(parseInt(text)) }
  }

  TextField
  {
    width:  220
    height: 50

    // focus: true
    placeholderText: "Square size: " + backend.getSquareSize().toString()
    font.pointSize: 14
    wrapMode: TextInput.Wrap
    validator: IntValidator {bottom: 10; top: 100;}

    background: Rectangle
    {
      radius: 5
      color:        parent.enabled      ? "lightGrey"   : "#353637"
      border.color: parent.activeFocus  ? "teal"        : "transparent"
      border.width: 2
    }

    onTextChanged:  { backend.setSquareSize(parseInt(text)) }
    onAccepted:     { backend.setSquareSize(parseInt(text)) }
  }

  TextField
  {
    width:  220
    height: 50

    // focus: true
    placeholderText: "Game speed: " + backend.getTimerPeriod().toString() + " ms"
    font.pointSize: 14
    wrapMode: TextInput.Wrap
    validator: IntValidator {bottom: 100; top: 5000;}

    background: Rectangle
    {
      radius: 5
      color:        parent.enabled      ? "lightGrey"   : "#353637"
      border.color: parent.activeFocus  ? "teal"        : "transparent"
      border.width: 2
    }

    onTextChanged:  { backend.setTimerPeriod(parseInt(text)) }
    onAccepted:     { backend.setTimerPeriod(parseInt(text)) }
  }
}