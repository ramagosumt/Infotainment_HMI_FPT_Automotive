cmake_minimum_required(VERSION 3.16)

project(WeatherApp_MVVM VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(appWeatherApp_MVVM
    main.cpp
)

qt_add_qml_module(appWeatherApp_MVVM
    URI WeatherApp_MVVM
    VERSION 1.0
    QML_FILES
        Main.qml
        ARHUDEditor.qml
        WeatherView.qml
        WeatherViewEditor.qml
        MediaView.qml
    SOURCES
        weathermodel.h weathermodel.cpp
        weatherviewmodel.h weatherviewmodel.cpp
        mediamodel.h mediamodel.cpp
        mediaviewmodel.h mediaviewmodel.cpp
        errormanager.h errormanager.cpp
    RESOURCES
        assets/fonts/Encode_Sans/static/EncodeSans-Thin.ttf
        assets/fonts/Encode_Sans/static/EncodeSans-ExtraLight.ttf
        assets/fonts/Encode_Sans/static/EncodeSans-Light.ttf
        assets/fonts/Encode_Sans/static/EncodeSans-Regular.ttf
        assets/fonts/Encode_Sans/static/EncodeSans-Medium.ttf
        assets/fonts/Encode_Sans/static/EncodeSans-SemiBold.ttf
        assets/fonts/Encode_Sans/static/EncodeSans-Bold.ttf
        assets/fonts/Encode_Sans/static/EncodeSans-ExtraBold.ttf
        assets/fonts/Encode_Sans/static/EncodeSans-Black.ttf
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

set_target_properties(appWeatherApp_MVVM PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWeatherApp_MVVM
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appWeatherApp_MVVM
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
