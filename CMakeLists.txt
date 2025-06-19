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
        SOURCES weathermodel.h weathermodel.cpp
        SOURCES weatherviewmodel.h weatherviewmodel.cpp
        QML_FILES WeatherView.qml
        QML_FILES WeatherViewEditor.qml
        QML_FILES
        RESOURCES assets/images/Cloudy100.png assets/images/PartlyCloudy100.png assets/images/Rainy100.png assets/images/Sunny100.png
        RESOURCES assets/images/Foggy100.png assets/images/Stormy100.png
        RESOURCES assets/fonts/Encode_Sans/static/EncodeSans-Thin.ttf
        QML_FILES
        QML_FILES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWeatherApp_MVVM PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWeatherApp_MVVM
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
