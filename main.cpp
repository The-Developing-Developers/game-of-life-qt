#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend.h"

int main(int argc, char *argv[])
{
  qmlRegisterUncreatableMetaObject
  (
    GameState_ns::staticMetaObject, // meta object created by Q_NAMESPACE macro
    "GameStateEnum",                // import statement (can be any string)
    1, 0,                           // major and minor version of the import
    "GameState",                    // name in QML (does not have to match C++ name)
    "Error: only enums"             // error in case someone tries to create a namespace object
  );

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
