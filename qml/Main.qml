import QtQuick
import QtQuick.Controls

ApplicationWindow
{
  id: main_root

  minimumWidth:  800
  minimumHeight: 600
  visible: true
  visibility: Qt.WindowFullScreen
  title: "Game Of Life"

  readonly property string  welcomeScreen: "WelcomeScreen.qml"
  readonly property string  gameScreen:    "GameBoard.qml"
           property bool    isGameActive:   false

  Loader
  {
    id: loader

    anchors.fill: main_root.contentItem
    source:       main_root.isGameActive ? gameScreen : welcomeScreen
  }

} // id: main_root