cmake_minimum_required(VERSION 3.16)

project(ARHUDTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

# === FFmpeg Integration ===
set(FFMPEG_ROOT_DIR "${CMAKE_SOURCE_DIR}/Plugins/ffmpeg")
set(FFMPEG_INCLUDE_DIR "${FFMPEG_ROOT_DIR}/include")
set(FFMPEG_LIB_DIR "${FFMPEG_ROOT_DIR}/lib")

# === GoogleTest ===
add_subdirectory(
    "${CMAKE_SOURCE_DIR}/Plugins/googletest"
    "${CMAKE_BINARY_DIR}/ARHUDTests/build-googletest"
)

enable_testing()

# === Source/Header Files ===
set(SOURCE_FILES
    Tests/UT/3D/OsmParser_UT.cpp

    Tests/UT/Error/ErrorManager_UT.cpp

    Tests/UT/Media/MediaModel_UT.cpp
    Tests/UT/Media/MediaViewModel_UT.cpp

    Tests/UT/Streaming/FFmpegDecoder_UT.cpp
    Tests/UT/Streaming/StreamingModel_UT.cpp
    Tests/UT/Streaming/StreamingViewModel_UT.cpp
    Tests/UT/Streaming/StreamingProvider_UT.cpp

    Tests/UT/Weather/WeatherModel_UT.cpp
    Tests/UT/Weather/WeatherViewModel_UT.cpp
)

qt_add_executable(appARHUDTests
    Tests/main.cpp
    ${SOURCE_FILES}
)

target_include_directories(appARHUDTests
    PRIVATE ${CMAKE_SOURCE_DIR}/Headers
)

target_link_libraries(appARHUDTests
    PRIVATE Qt6::Quick
    PRIVATE gtest
    PRIVATE gtest_main
    PRIVATE arhudcore
)

set_target_properties(appARHUDTests PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# === DLL Copy Logic ===

set(MINGW_BIN "C:/Toolbox/Qt/Tools/mingw1310_64/bin")
set(QT_BIN "${Qt6_DIR}/../../../bin")
set(QT_PLUGIN_PLATFORMS "${Qt6_DIR}/../../../plugins/platforms")

# Core Qt DLLs
set(QT_DLLS
    Qt6Core.dll
    Qt6Quick.dll
    Qt6Qml.dll
    Qt6Gui.dll
    Qt6Network.dll
    Qt6OpenGL.dll
    Qt6QmlModels.dll
    Qt6QmlWorkerScript.dll
    Qt6QmlMeta.dll
    Qt6Scxml.dll
    Qt6Positioning.dll
)

foreach(dll IN LISTS QT_DLLS)
    add_custom_command(TARGET appARHUDTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${QT_BIN}/${dll}"
            $<TARGET_FILE_DIR:appARHUDTests>
    )
endforeach()

# Qt platform plugin
add_custom_command(TARGET appARHUDTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:appARHUDTests>/platforms"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${QT_PLUGIN_PLATFORMS}/qwindows.dll"
        "$<TARGET_FILE_DIR:appARHUDTests>/platforms"
)

# FFmpeg DLLs
foreach(dll IN ITEMS avcodec-61.dll avformat-61.dll avutil-59.dll swresample-5.dll swscale-8.dll)
    add_custom_command(TARGET appARHUDTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FFMPEG_ROOT_DIR}/bin/${dll}"
            $<TARGET_FILE_DIR:appARHUDTests>
    )
endforeach()

# MinGW runtime DLLs
foreach(dll IN ITEMS libstdc++-6.dll libgcc_s_seh-1.dll libwinpthread-1.dll)
    add_custom_command(TARGET appARHUDTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MINGW_BIN}/${dll}"
            $<TARGET_FILE_DIR:appARHUDTests>
    )
endforeach()

# === Test Discovery ===
include(GoogleTest)
gtest_discover_tests(appARHUDTests)

# === Install Rules ===
include(GNUInstallDirs)
install(TARGETS appARHUDTests
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
