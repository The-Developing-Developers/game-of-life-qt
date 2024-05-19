/**
 * @file main.cpp
 *
 * @brief Entry point of the application. The C++ class 'GameManager' is instantiated here, and passed to the QML engine front-end to be
 * used in QML code. The 'GameManager' acts as a coordinator of the whole application, relaying information from the QML front-end to the
 * C++ back-end.
 **/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "gamemanager.hpp"

int main(int argc, char *argv[])
{
  GameManager           gameManager; // This class acts as a coordinator of the whole application, relaying information from the QML front-end to the C++ back-end.
  QGuiApplication       app(argc, argv);
  QQmlApplicationEngine engine; // QML engine instantiation must go after the instantiation of the back-end class 'GameManager'.
  QQmlContext*          context = engine.rootContext(); // Root context of the engine (needed to attach proprieties o C++ classes at run-time).

  context->setContextProperty("gameManager",    &gameManager); // Now the `GameManager` C++ class is usable in QML with the 'gameManager' identifier.
  context->setContextProperty("patternsModel", gameManager.getPatternPointerForQmlContext()); // The 'GameManager' already instantiates a `Patterns` object in its constructor. Therefore, we can use that instance instead of creating a new one to pass to the QML front-end.
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  const QUrl url(u"qrc:/qml/Main.qml"_qs); // Entry point for the QML engine.
  engine.load(url);

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
