
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "screenshothelper.hpp"
#include "SystemEventFilter.hpp"
#include <QCursor>

#define QML_PACKAGE_NAME "com.xul.st"



int main(int argc, char *argv[])
{
    const QUrl url(u"qrc:/SnipingTester/Main.qml"_qs);//QML APPP ENTRY POINT

//    //Static configurations
//    auto cursor =  QCursor(Qt::CursorShape::CrossCursor);
//    QGuiApplication::setOverrideCursor(cursor); // Set the cursor to a wait cursor

    //REGISTER TYPES (MOVE TO A SEPARATE CLASS)
    qmlRegisterSingletonType<ScreenshotHelper>(QML_PACKAGE_NAME, 1, 0 , "ScreenshotHelper",[](QQmlEngine* engine, QJSEngine* scriptEngine) -> QObject*
                                               {
                                                   Q_UNUSED(engine)
                                                   Q_UNUSED(scriptEngine)
                                                   auto helper = new ScreenshotHelper();
                                                   return helper;
                                               });

    //Initialize the app
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    SystemEventFilter eventFilter;

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    //Install key filters...
    app.installEventFilter(&eventFilter);

    return app.exec();
}
