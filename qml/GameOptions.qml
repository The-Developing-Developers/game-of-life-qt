import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Row
{
  spacing: 50

  Column
  {
    id: rowsCol

    Text
    {
      anchors.horizontalCenter: rowsCol.horizontalCenter
      text: "Number of rows:"
      font.pointSize: 14
    }

    TextField
    {
      width:  220
      height: 50

      focus: true
      placeholderText: "Rows: " + backend.getNumOfRows().toString()
      font.pointSize: 14
      wrapMode: TextInput.Wrap
      validator: IntValidator {bottom: 1; top: 12;}

      background: Rectangle
      {
        radius: 5
        color:        parent.enabled      ? "lightGrey"   : "#353637"
        border.color: parent.activeFocus  ? "teal"        : "black"
        border.width: parent.activeFocus  ? 3 : 1
      }

      onTextChanged:  { backend.setNumOfRows(parseInt(text)) }
      onAccepted:     { backend.setNumOfRows(parseInt(text)) }
    }
  }

  Column
  {
    id: colsCol

    Text
    {
      anchors.horizontalCenter: colsCol.horizontalCenter
      text: "Number of columns:"
      font.pointSize: 14
    }

    TextField
    {
      width:  220
      height: 50

      placeholderText: "Columns: " + backend.getNumOfCols().toString()
      font.pointSize: 14
      wrapMode: TextInput.Wrap
      validator: IntValidator {bottom: 1; top: 25;}

      background: Rectangle
      {
        radius: 5
        color:        parent.enabled      ? "lightGrey"   :  "#353637"
        border.color: parent.activeFocus  ? "teal"        : "black"
        border.width: parent.activeFocus  ? 3 : 1
      }

      onTextChanged:  { backend.setNumOfCols(parseInt(text)) }
      onAccepted:     { backend.setNumOfCols(parseInt(text)) }
    }
  }

  Column
  {
    id: squareSizeCol

    Text
    {
      anchors.horizontalCenter: squareSizeCol.horizontalCenter
      text: "Square size:"
      font.pointSize: 14
    }

    TextField
    {
      width:  220
      height: 50

      placeholderText: "Square size: " + backend.getSquareSize().toString()
      font.pointSize: 14
      wrapMode: TextInput.Wrap
      validator: IntValidator {bottom: 10; top: 100;}

      background: Rectangle
      {
        radius: 5
        color:        parent.enabled      ? "lightGrey"   : "#353637"
        border.color: parent.activeFocus  ? "teal"        : "black"
        border.width: parent.activeFocus  ? 3 : 1
      }

      onTextChanged:  { backend.setSquareSize(parseInt(text)) }
      onAccepted:     { backend.setSquareSize(parseInt(text)) }
    }
  }

  Column
  {
    id: gameSpeedCol

    Text
    {
      anchors.horizontalCenter: gameSpeedCol.horizontalCenter
      text: "Refresh period (ms):"
      font.pointSize: 14
    }

    TextField
    {
      width:  220
      height: 50

      placeholderText: "Game speed: " + backend.getTimerPeriod().toString() + " ms"
      font.pointSize: 14
      wrapMode: TextInput.Wrap
      validator: IntValidator {bottom: 100; top: 5000;}

      background: Rectangle
      {
        radius: 5
        color:        parent.enabled      ? "lightGrey"   : "#353637"
        border.color: parent.activeFocus  ? "teal"        : "black"
        border.width: parent.activeFocus  ? 3 : 1
      }

      onTextChanged:  { backend.setTimerPeriod(parseInt(text)) }
      onAccepted:     { backend.setTimerPeriod(parseInt(text)) }
    }
  }
} // Row