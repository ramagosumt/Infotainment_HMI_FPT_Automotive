cmake_minimum_required(VERSION 3.16)

project(WeatherApp_MVVM VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Scxml)

# === Source Files ===
set(SOURCE_FILES
    Sources/weathermodel.cpp
    Sources/weatherviewmodel.cpp
    Sources/mediamodel.cpp
    Sources/mediaviewmodel.cpp
    Sources/mediasampleapi.cpp
    Sources/streamingmodel.cpp
    Sources/streamingviewmodel.cpp
    Sources/errormanager.cpp
    Sources/main.cpp
)

# === Header Files ===
set(HEADER_FILES
    Headers/weathermodel.h
    Headers/weatherviewmodel.h
    Headers/mediamodel.h
    Headers/mediaviewmodel.h
    Headers/mediasampleapi.h
    Headers/streamingmodel.h
    Headers/streamingviewmodel.h
    Headers/errormanager.h
)

# === QML Files ===
set(QML_FILES
    QML/ARHUD.qml
    QML/ARHUDEditor.qml
    QML/WeatherView.qml
    QML/MediaView.qml
    QML/StreamingView.qml
)

# === Asset Files ===
set(FONT_FILES
    assets/fonts/Encode_Sans/static/EncodeSans-Thin.ttf
    assets/fonts/Encode_Sans/static/EncodeSans-ExtraLight.ttf
    assets/fonts/Encode_Sans/static/EncodeSans-Light.ttf
    assets/fonts/Encode_Sans/static/EncodeSans-Regular.ttf
    assets/fonts/Encode_Sans/static/EncodeSans-Medium.ttf
    assets/fonts/Encode_Sans/static/EncodeSans-SemiBold.ttf
    assets/fonts/Encode_Sans/static/EncodeSans-Bold.ttf
    assets/fonts/Encode_Sans/static/EncodeSans-ExtraBold.ttf
    assets/fonts/Encode_Sans/static/EncodeSans-Black.ttf
)

set(IMAGE_FILES
    assets/images/media/AmazonMusic100.png
    assets/images/media/AppleMusic100.png
    assets/images/media/Radio100.png
    assets/images/media/SoundCloud100.png
    assets/images/media/Spotify100.png
    assets/images/media/USB100.png
    assets/images/weather/Cloudy100.png
    assets/images/weather/Foggy100.png
    assets/images/weather/PartlyCloudy100.png
    assets/images/weather/Rainy100.png
    assets/images/weather/Stormy100.png
    assets/images/weather/Sunny100.png
)

# === SCXML File ===
set(SCXML_FILE
    ErrorManager.scxml
)

# === Executable ===
qt_add_executable(appWeatherApp_MVVM
    Sources/main.cpp
)

# === QML Module with Grouped Resources ===
qt_add_qml_module(appWeatherApp_MVVM
    URI WeatherApp_MVVM
    VERSION 1.0
    QML_FILES ${QML_FILES}
    SOURCES ${SOURCE_FILES} ${HEADER_FILES}
    RESOURCES ${SCXML_FILE} ${FONT_FILES} ${IMAGE_FILES}
)

# === Include Directories ===
target_include_directories(appWeatherApp_MVVM
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Headers
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources
)

# === Target Properties ===
set_target_properties(appWeatherApp_MVVM PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION           ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING     ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE                          TRUE
    WIN32_EXECUTABLE                       TRUE
)

# === Linking ===
target_link_libraries(appWeatherApp_MVVM
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Scxml
)

# === Install Rules ===
include(GNUInstallDirs)

install(TARGETS appWeatherApp_MVVM
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
