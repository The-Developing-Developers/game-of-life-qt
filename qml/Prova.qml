// https://forum.qt.io/topic/63926/qml-item-binding-loop-detected-for-property-width/2

import QtQuick
import QtQuick.Window
import QtQuick.Controls

ApplicationWindow
{
  id: applicationWindow1

  width:  800 /* container.width  + 2 * margins */
  height: 600 /* container.height + 2 * margins */
  title: "Lab5"
  visible: true
  property int margins: 4

  Connections
  {
    target: transitionPoint
    function onSendDataToQml()
    {
      outputText.text = outStr
    }
  }

  MouseArea
  {
    anchors.fill: parent
    onClicked:
    {
      transitionPoint.receiveDataFromQml(dataInputField.text)
    }
    // signal: sendDataToQml()
  }

  Item
  {
    id: container
    // width:  600 /* childrenRect.width */
    // height: 500 /* childrenRect.height */
    width: dataInputField.width
    height: outputText.height + dataInputField.height
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter

    Text
    {
      id: outputText
      text: "Lambda"
      wrapMode: Text.WordWrap
      textFormat: Text.PlainText
      verticalAlignment: Text.AlignVCenter
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: parent.top
    }

    TextField
    {
      id: dataInputField
      width: 110
      placeholderText: "enter fraction data"
      anchors.horizontalCenter: outputText.horizontalCenter
      anchors.top: outputText.bottom
      anchors.topMargin: 3
    }
  }
}
