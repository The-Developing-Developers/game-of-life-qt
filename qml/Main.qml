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

  Item
  {
    id: rootContainer // needed for the `state` property

    anchors.fill: root.contentItem

    Loader
    {
      id: loader

      anchors.fill: rootContainer
      // source: assigned by `state` property
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
        PropertyChanges { target: loader; source: "WelcomeScreen.qml"; }
      },

      State
      {
        name: "gameScreen"
        PropertyChanges { target: loader; source: "GameBoard.qml"; }
      }
    ]
  } // rootContainer
} // root