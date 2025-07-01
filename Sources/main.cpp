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

    // Models
    WeatherModel weatherModel;
    MediaModel mediaModel;

    // ViewModels
    WeatherViewModel weatherViewModel(&weatherModel);
    MediaViewModel mediaViewModel(&mediaModel);

    // Global context properties
    engine.rootContext()->setContextProperty("weatherViewModel", &weatherViewModel);
    engine.rootContext()->setContextProperty("mediaViewModel", &mediaViewModel);

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

    QQmlComponent editorComponent(&engine, QUrl("qrc:/WeatherApp_MVVM/QML/ARHUDEditor.qml"));
    QObject* editorWindow = editorComponent.create(editorContext);
    if (!editorWindow) qWarning("Failed to create ARHUDEditor window.");

    return app.exec();
}
