import QtQuick
import QtQuick.Controls

Grid
{
  id: root

  columns: 3
  columnSpacing: 50
     rowSpacing: 10

  property int fontPointSize: 14

  Column
  {
    id: numOfRows

    Text
    {
      anchors.horizontalCenter: numOfRows.horizontalCenter
      text: "Num. of rows"
      font.pointSize: fontPointSize
    }

    CustomTextField
    {
      placeholderText: "Rows: " + gameManager.getNumOfRows().toString()
      onTextChanged:  { gameManager.setNumOfRows(parseInt(text)) }
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

    CustomTextField
    {
      placeholderText: "Columns: " + gameManager.getNumOfCols().toString()
      onTextChanged:  { gameManager.setNumOfCols(parseInt(text)) }
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

    CustomTextField
    {
      placeholderText: "Square size: " + gameManager.getSquareSize().toString()
      onTextChanged:  { gameManager.setSquareSize(parseInt(text)) }
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

    CustomTextField
    {
      placeholderText: "Period: " + gameManager.getTimerPeriod().toString() + " ms"
      onTextChanged:  { gameManager.setTimerPeriod(parseInt(text)) }
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

    CustomTextField
    {
      placeholderText: "Spacing: " + gameManager.getSquareSpacing().toString() + " px"
      onTextChanged:  { gameManager.setSquareSpacing(parseInt(text)) }
    }
  }
} // Row