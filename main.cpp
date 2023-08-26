#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend.h"

int main(int argc, char *argv[])
{
  Backend               backend;
  QGuiApplication       app(argc, argv);
  QQmlApplicationEngine engine; // Motore QML
  QQmlContext*          context = engine.rootContext(); // Root context del motore (serve per agganciare proprietà o classi C++ in run-time, nel nostro caso la classe Scene)

  context->setContextProperty("backend", &backend); // Aggancio della classe Scene, ora usabile in QML
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  const QUrl url(u"qrc:/qml/Main.qml"_qs);
  engine.load(url);

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
