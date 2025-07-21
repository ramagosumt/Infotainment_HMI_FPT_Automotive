#include <QGuiApplication>            // Provides core application functionality for GUI apps
#include <QQmlApplicationEngine>      // Loads and manages QML files
#include <QQmlContext>                // Allows exposing C++ objects to QML
#include <QQmlComponent>              // Used to manually create QML components
#include <QScxmlStateMachine>         // Provides SCXML-based state machine support

#include "Weather/weatherviewmodel.h"         // Weather ViewModel header
#include "Media/mediaviewmodel.h"           // Media ViewModel header
#include "Streaming/streamingviewmodel.h"       // Streaming ViewModel header
#include "Streaming/streamingprovider.h"        // Provides image frames for video streaming
#include "Error/errormanager.h"             // Error management logic

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);                                // Initialize Qt GUI application
    QQmlApplicationEngine engine;                                   // Create QML engine

    // Models
    WeatherModel    weatherModel;                                   // Weather raw data model
    MediaModel      mediaModel;                                     // Media raw data model
    StreamingModel  streamingModel;                                 // Streaming raw data model

    // ViewModels
    WeatherViewModel   weatherViewModel(&weatherModel);             // Weather ViewModel, connects to WeatherModel
    MediaViewModel     mediaViewModel(&mediaModel);                 // Media ViewModel, connects to MediaModel
    StreamingViewModel streamingViewModel(&streamingModel);         // Streaming ViewModel, connects to StreamingModel

    // Error Manager
    ErrorManager errorManager;                                      // Handles system error states

    // Provider
    StreamingProvider* streamingProvider = new StreamingProvider(); // Image provider for video frames

    // Global context properties
    engine.rootContext()->setContextProperty("weatherViewModel",   &weatherViewModel);          // Expose WeatherViewModel to QML
    engine.rootContext()->setContextProperty("mediaViewModel",     &mediaViewModel);            // Expose MediaViewModel to QML
    engine.rootContext()->setContextProperty("streamingViewModel", &streamingViewModel);        // Expose StreamingViewModel to QML
    engine.rootContext()->setContextProperty("errorManager",       &errorManager);              // Expose ErrorManager to QML

    // Editor
    QQmlComponent editorComponent(&engine, QUrl("qrc:/WeatherApp_MVVM/QML/ARHUDEditor.qml"));   // Load Editor QML component
    QObject* editorWindow = editorComponent.create();                                           // Create Editor window object

    engine.rootContext()->setContextProperty("editorWindow",        editorWindow);              // Expose Editor window to QML
    engine.addImageProvider("streamingProvider",                    streamingProvider);         // Register image provider under 'videoFrameProvider' ID

    // Connect frame updates from StreamingViewModel to StreamingProvider
    QObject::connect(&streamingViewModel, &StreamingViewModel::onCurrentFrameUpdated, [&]() {
        streamingProvider->setFrame(streamingViewModel.getCurrentFrame());                      // Update image provider with latest frame
    });

    QString assetPath = QCoreApplication::applicationDirPath() + "/WeatherApp_MVVM/assets/videos/map.mp4";
    streamingViewModel.setInputPath(assetPath);                                             // Set video input path for streaming

    streamingViewModel.startDecoding(240, 135);                                             // Start video decoding

    // Load Main QML
    const QUrl mainUrl(QStringLiteral("qrc:/WeatherApp_MVVM/QML/ARHUD.qml"));               // Main QML file URL
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [mainUrl](QObject* obj, const QUrl& objUrl) {                                       // Exit app if root object fails to load
            if (!obj && objUrl == mainUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
        );

    engine.load(mainUrl);                                                                   // Load Main QML into engine
    if (engine.rootObjects().isEmpty()) return -1;                                          // Exit if no root object loaded

    // Optional: Access root windows if needed
    QObject* rootObject      = engine.rootObjects().first();                                // Get root QML object
    QObject* weatherViewRoot = rootObject->findChild<QObject*>("weatherViewWindow");        // Find Weather View window in QML
    QObject* mediaViewRoot   = rootObject->findChild<QObject*>("mediaViewWindow");          // Find Media View window in QML
    QObject* streamingViewRoot   = rootObject->findChild<QObject*>("streamingViewWindow");  // Find Streaming View window in QML

    // Create Editor Window with extended context
    QQmlContext* editorContext = new QQmlContext(engine.rootContext());                     // Create new context for Editor window
    editorContext->setContextProperty("weatherViewModel",       &weatherViewModel);         // Expose WeatherViewModel to Editor
    editorContext->setContextProperty("mediaViewModel",         &mediaViewModel);           // Expose MediaViewModel to Editor
    editorContext->setContextProperty("weatherViewWindow",      weatherViewRoot);           // Expose Weather window to Editor
    editorContext->setContextProperty("mediaViewWindow",        mediaViewRoot);             // Expose Media window to Editor
    editorContext->setContextProperty("streamingViewWindow",    streamingViewRoot);         // Expose Streaming window to Editor
    editorContext->setContextProperty("errorManager",           &errorManager);             // Expose ErrorManager to Editor

    return app.exec();                                                                      // Run the application event loop
}
