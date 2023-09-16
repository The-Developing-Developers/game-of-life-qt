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

    Loader
    {
      id: loader

      anchors.fill: rootContainer
      // source: assigned by `state` property
    }

    Connections // equivalent to C++ connect(&gameManager, &GameManager::gameStateChanged, this, &Component::onGameStateChanged)
    {
      target: gameManager

      function onGameStateChanged(currentState)
      {
        switch ( currentState )
        {
          case GameState.WelcomeScreen:
            rootContainer.state = rootContainer.welcomeScreen
            break;

          case GameState.GameBoard:
            rootContainer.state = rootContainer.gameScreen
            break;

          case GameState.Undefined:
          default:
            console.log("Main.qml: unknown error during state change")
            break;
        }
      }
    }

    state: rootContainer.welcomeScreen // default state

    states:
    [
      State
      {
        name: rootContainer.welcomeScreen
        PropertyChanges { target: loader; source: "WelcomeScreen.qml"; }
      },

      State
      {
        name: rootContainer.gameScreen
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