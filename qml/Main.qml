import QtQuick
import QtQuick.Controls

ApplicationWindow
{
  id: root

  minimumWidth:  800
  minimumHeight: 600
  visible: true
  visibility: Qt.WindowFullScreen
  title: qsTr("Game Of Life")

  Rectangle
  {
    id: rootContainer

    anchors.fill: parent

    Loader
    {
      id: loader

      property bool startGame: false // assigned by binding in WelcomeScreen.qml
      anchors.fill: parent
      // source: assigned by "state" property

      // onLoaded:{ console.log("loaded file: " + source) } // TODO: debug
    }

    state: "welcomeScreen" // default state

    states:
    [
      State
      {
        name: "welcomeScreen"
        when: loader.startGame === false
        PropertyChanges { target: loader; source: "WelcomeScreen.qml"; }
      },

      State
      {
        name: "gameScreen"
        when: loader.startGame === true
        PropertyChanges { target: loader; source: "GameBoard.qml"; }
      }
    ]
  } // rootContainer
} // root