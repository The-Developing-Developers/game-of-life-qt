#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend.h"

int main(int argc, char *argv[])
{
  GameManager           gameManager;
  QGuiApplication       app(argc, argv);
  QQmlApplicationEngine engine; // QML engine instantiation must go after the instantiation of the back-end class
  QQmlContext*          context = engine.rootContext(); // Root context of the engine (needed to attach proprieties o C++ classes at run-time)

  context->setContextProperty("gameManager", &gameManager); // Now the `GameManager` C++ class is usable in QML
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  const QUrl url(u"qrc:/qml/Main.qml"_qs); // Entry point for the QML engine
  engine.load(url);

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
