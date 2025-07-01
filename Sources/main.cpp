#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QScxmlStateMachine>

#include "weatherviewmodel.h"
#include "mediaviewmodel.h"
#include "errormanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Models
    WeatherModel weatherModel;
    MediaModel mediaModel;

    // ViewModels
    WeatherViewModel weatherViewModel(&weatherModel);
    MediaViewModel mediaViewModel(&mediaModel);

    // Error Manager
    ErrorManager errorManager;

    // Global context properties
    engine.rootContext()->setContextProperty("weatherViewModel", &weatherViewModel);
    engine.rootContext()->setContextProperty("mediaViewModel", &mediaViewModel);
    engine.rootContext()->setContextProperty("errorManager", &errorManager);

    QQmlComponent editorComponent(&engine, QUrl("qrc:/WeatherApp_MVVM/QML/ARHUDEditor.qml"));
    QObject* editorWindow = editorComponent.create();
    engine.rootContext()->setContextProperty("editorWindow", editorWindow);

    // Load Main QML
    const QUrl mainUrl(QStringLiteral("qrc:/WeatherApp_MVVM/QML/ARHUD.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [mainUrl](QObject *obj, const QUrl &objUrl) {
            if (!obj && objUrl == mainUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
        );

    engine.load(mainUrl);
    if (engine.rootObjects().isEmpty()) return -1;

    // Optional: Access root windows if needed
    QObject* rootObject = engine.rootObjects().first();
    QObject* weatherViewRoot = rootObject->findChild<QObject*>("weatherViewWindow");
    QObject* mediaViewRoot = rootObject->findChild<QObject*>("mediaViewWindow");

    // Create Editor Window with extended context
    QQmlContext* editorContext = new QQmlContext(engine.rootContext());
    editorContext->setContextProperty("weatherViewModel", &weatherViewModel);
    editorContext->setContextProperty("mediaViewModel", &mediaViewModel);
    editorContext->setContextProperty("weatherViewWindow", weatherViewRoot);
    editorContext->setContextProperty("mediaViewWindow", mediaViewRoot);
    editorContext->setContextProperty("errorManager", &errorManager);

    return app.exec();
}
