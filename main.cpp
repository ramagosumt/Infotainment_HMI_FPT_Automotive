#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>

#include "weatherviewmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    WeatherViewModel weatherViewModel;
    engine.rootContext()->setContextProperty("weatherViewModel", &weatherViewModel);

    const QUrl url(QStringLiteral("qrc:/WeatherApp_MVVM/WeatherView.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    QObject *rootObject = engine.rootObjects().first();

    QObject *weatherViewRoot = rootObject->objectName() == "weatherViewWindow"
                                   ? rootObject
                                   : rootObject->findChild<QObject*>("weatherViewWindow");

    QQmlContext *context = new QQmlContext(engine.rootContext());
    context->setContextProperty("weatherViewModel", &weatherViewModel);
    context->setContextProperty("weatherViewWindow", weatherViewRoot);

    QQmlComponent editorComponent(&engine, QUrl("qrc:/WeatherApp_MVVM/WeatherViewEditor.qml"));
    QObject *editorWindow = editorComponent.create(context);

    return app.exec();
}
