import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Grid
{
  id: root

  columns: 3
  columnSpacing: 50
     rowSpacing: 10

  property int textFieldWidth:  160
  property int textFieldHeight:  50
  property int fontPointSize:    14

  Column
  {
    id: numOfRows

    Text
    {
      anchors.horizontalCenter: numOfRows.horizontalCenter
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
    id: numOfCols

    Text
    {
      anchors.horizontalCenter: numOfCols.horizontalCenter
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
    id: squareSize

    Text
    {
      anchors.horizontalCenter: squareSize.horizontalCenter
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
    id: refreshPeriod

    Text
    {
      anchors.horizontalCenter: refreshPeriod.horizontalCenter
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

  Column
  {
    id: squareSpacing

    Text
    {
      anchors.horizontalCenter: squareSpacing.horizontalCenter
      text: "Square spacing"
      font.pointSize: fontPointSize
    }

    TextField
    {
      width:  textFieldWidth
      height: textFieldHeight

      placeholderText: "Spacing: " + backend.getSquareSpacing().toString() + " px"
      font.pointSize: fontPointSize
      wrapMode: TextInput.Wrap

      background: Rectangle
      {
        radius: 5
        color:        parent.enabled      ? "lightGrey"   : "#353637"
        border.color: parent.activeFocus  ? "teal"        : "black"
        border.width: parent.activeFocus  ? 3 : 1
      }

      onTextChanged:  { backend.setSquareSpacing(parseInt(text)) }
      onAccepted:     { backend.setSquareSpacing(parseInt(text)) }
    }
  }
} // Row