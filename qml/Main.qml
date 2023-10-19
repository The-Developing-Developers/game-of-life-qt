import QtQuick
import QtQuick.Controls
import GameStateEnum

ApplicationWindow
{
  id: root

  minimumWidth:  800
  minimumHeight: 600
  visible: true
  visibility: Qt.WindowFullScreen
  title: qsTr("Game Of Life")

  Item // needed for the `state` property
  {
    id: rootContainer

    anchors.fill: root.contentItem

    readonly property string welcomeScreen: "welcomeScreen"
    readonly property string gameScreen: "gameScreen"
             property bool   isGameActive: false

    Loader
    {
      id: loader

      anchors.fill: rootContainer
      source: rootContainer.isGameActive ? "GameBoard.qml" : "WelcomeScreen.qml"
    }

  } // rootContainer
} // id: root