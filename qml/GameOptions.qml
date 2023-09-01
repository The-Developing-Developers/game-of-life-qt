import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Row
{
  id: root

  spacing: 20

  property int textFieldWidth:  160
  property int textFieldHeight:  50
  property int fontPointSize:    14

  Column
  {
    id: rowsCol

    Text
    {
      anchors.horizontalCenter: rowsCol.horizontalCenter
      text: "Num. of rows"
      font.pointSize: fontPointSize
    }

    TextField
    {
      width:  textFieldWidth
      height: textFieldHeight

      focus: true
      placeholderText: "Rows: " + backend.getNumOfRows().toString()
      font.pointSize: fontPointSize
      wrapMode: TextInput.Wrap

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
      text: "Num. of columns"
      font.pointSize: fontPointSize
    }

    TextField
    {
      width:  textFieldWidth
      height: textFieldHeight

      placeholderText: "Columns: " + backend.getNumOfCols().toString()
      font.pointSize: fontPointSize
      wrapMode: TextInput.Wrap

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
      text: "Square size"
      font.pointSize: fontPointSize
    }

    TextField
    {
      width:  textFieldWidth
      height: textFieldHeight

      placeholderText: "Square size: " + backend.getSquareSize().toString()
      font.pointSize: fontPointSize
      wrapMode: TextInput.Wrap

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
      text: "Refresh period (ms)"
      font.pointSize: fontPointSize
    }

    TextField
    {
      width:  textFieldWidth
      height: textFieldHeight

      placeholderText: "Period: " + backend.getTimerPeriod().toString() + " ms"
      font.pointSize: fontPointSize
      wrapMode: TextInput.Wrap

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