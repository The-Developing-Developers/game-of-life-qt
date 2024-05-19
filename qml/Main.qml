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
           property bool    resetGameBoard: false

  Loader
  {
    id: loader

    anchors.fill: main_root.contentItem // So that the Loader completely fills the `main_root`
    source:       main_root.isGameActive ? (main_root.resetGameBoard ? "" : gameScreen) : welcomeScreen // The application starts on the `welcomeScreen`. When a new shape is selected in the `shapeSelectorPopup`, the `GameBoard` will raise and lower the `resetGameBoard` to redraw the game grid
  }

} // id: main_root