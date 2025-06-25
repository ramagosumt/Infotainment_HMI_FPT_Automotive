#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>

#include "weatherviewmodel.h"
#include "mediaviewmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    WeatherViewModel weatherViewModel;
    MediaViewModel mediaViewModel;

    engine.rootContext()->setContextProperty("weatherViewModel", &weatherViewModel);
    engine.rootContext()->setContextProperty("mediaViewModel", &mediaViewModel);

    const QUrl url(QStringLiteral("qrc:/WeatherApp_MVVM/Main.qml"));
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

    QObject *mediaViewRoot = rootObject->objectName() == "mediaViewWindow"
                                   ? rootObject
                                   : rootObject->findChild<QObject*>("mediaViewWindow");

    QQmlContext *context = new QQmlContext(engine.rootContext());
    context->setContextProperty("weatherViewModel", &weatherViewModel);
    context->setContextProperty("mediaViewModel", &mediaViewModel);
    context->setContextProperty("weatherViewWindow", weatherViewRoot);
    context->setContextProperty("mediaViewWindow", mediaViewRoot);

    QQmlComponent editorComponent(&engine, QUrl("qrc:/WeatherApp_MVVM/ARHUDEditor.qml"));
    QObject *editorWindow = editorComponent.create(context);

    return app.exec();
}
