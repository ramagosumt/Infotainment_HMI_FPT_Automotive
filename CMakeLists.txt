cmake_minimum_required(VERSION 3.16)

project(ARHUDProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Scxml Positioning)

# === FFmpeg Integration ===
set(FFMPEG_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Plugins/ffmpeg")
set(FFMPEG_INCLUDE_DIR "${FFMPEG_ROOT_DIR}/include")
set(FFMPEG_LIB_DIR "${FFMPEG_ROOT_DIR}/lib")

message(STATUS "FFMPEG_LIB_DIR=${FFMPEG_LIB_DIR}")

# === Source/Header Files ===
set(SOURCE_FILES
    Sources/3D/osmparser.cpp

    Sources/Error/errormanager.cpp

    Sources/Media/mediamodel.cpp
    Sources/Media/mediaviewmodel.cpp
    Sources/Media/mediasampleapi.cpp

    Sources/Streaming/ffmpegdecoder.cpp
    Sources/Streaming/streamingmodel.cpp
    Sources/Streaming/streamingviewmodel.cpp
    Sources/Streaming/streamingprovider.cpp

    Sources/Weather/weathermodel.cpp
    Sources/Weather/weatherviewmodel.cpp
)

set(HEADER_FILES
    Headers/3D/osmparser.h

    Headers/Error/errormanager.h

    Headers/Media/mediamodel.h
    Headers/Media/mediaviewmodel.h
    Headers/Media/mediasampleapi.h

    Headers/Streaming/ffmpegdecoder.h
    Headers/Streaming/streamingmodel.h
    Headers/Streaming/streamingviewmodel.h
    Headers/Streaming/streamingprovider.h

    Headers/Weather/weathermodel.h
    Headers/Weather/weatherviewmodel.h
)

# === QML/Resource Files ===
set(QML_FILES
    QML/ARHUD.qml
    QML/ARHUDEditor.qml
    QML/WeatherView.qml
    QML/MediaView.qml
    QML/StreamingView.qml
)

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

set(VIDEO_FILES
    assets/videos/map.mp4
)

set(SCXML_FILE
    ErrorManager.scxml
)

# === Header Files ===
source_group("Header Files" FILES ${HEADER_FILES})

# === Source Files ===
source_group("Source Files" FILES ${SOURCE_FILES} ${QML_FILES})

# === Resources ===
source_group("Resources" FILES ${FONT_FILES} ${IMAGE_FILES} ${VIDEO_FILES})

# === State Charts ===
source_group("State charts" FILES ${SCXML_FILE})

# === Core ARHUD Library ===
add_library(arhudcore STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_include_directories(arhudcore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Headers
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources
    ${FFMPEG_INCLUDE_DIR}
)

target_link_libraries(arhudcore PUBLIC
    Qt6::Quick Qt6::Scxml Qt6::Positioning
    "${FFMPEG_LIB_DIR}/libavcodec.dll.a"
    "${FFMPEG_LIB_DIR}/libavformat.dll.a"
    "${FFMPEG_LIB_DIR}/libavutil.dll.a"
    "${FFMPEG_LIB_DIR}/libswresample.dll.a"
    "${FFMPEG_LIB_DIR}/libswscale.dll.a"
)

qt_policy(SET QTP0004 NEW)

qt_add_executable(appARHUDProject
    Sources/main.cpp
)

qt_add_qml_module(appARHUDProject
    URI ARHUDProject
    VERSION 1.0
    QML_FILES ${QML_FILES}
    RESOURCES ${SCXML_FILE} ${FONT_FILES} ${IMAGE_FILES} ${VIDEO_FILES}
)

target_link_libraries(appARHUDProject PRIVATE arhudcore)

set_target_properties(appARHUDProject PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION           ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING     ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE                          TRUE
    WIN32_EXECUTABLE                       TRUE
)

# === Copy FFmpeg DLLs After Build ===
add_custom_command(TARGET appARHUDProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${FFMPEG_ROOT_DIR}/bin/avcodec-61.dll"
        "${FFMPEG_ROOT_DIR}/bin/avformat-61.dll"
        "${FFMPEG_ROOT_DIR}/bin/avutil-59.dll"
        "${FFMPEG_ROOT_DIR}/bin/swresample-5.dll"
        "${FFMPEG_ROOT_DIR}/bin/swscale-8.dll"
        $<TARGET_FILE_DIR:appARHUDProject>
)

# === Install Rules ===
include(GNUInstallDirs)

install(TARGETS appARHUDProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# === External Tests ===
add_subdirectory(ARHUDTests)
