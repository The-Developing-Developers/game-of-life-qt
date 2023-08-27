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

    Connections
    {
      target: backend

      function onGameStateChanged()
      {
        switch ( backend.getGameState() )
        {
          case GameState.WelcomeScreen:
            rootContainer.state = "welcomeScreen"
            break;

          case GameState.GameBoard:
            rootContainer.state = "gameScreen"
            break;

          case GameState.Undefined:
          default:
            console.log("Main.qml: unknown error during state change")
            break;
        }
      }
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