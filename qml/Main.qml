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

    Loader
    {
      id: loader

      anchors.fill: rootContainer
      // source: assigned by `state` property
    }

    Connections
    {
      target: gameManager

      function onGameStateChanged(currentState)
      {
        switch ( currentState )
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

  Component.onCompleted:
  {
    // The finite-state machine is kick-started here
    gameManager.changeGameState(GameState.WelcomeScreen);
  }
} // id: root