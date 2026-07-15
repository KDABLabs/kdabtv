# Minimum required CMake version
cmake_minimum_required(VERSION 3.16)

# Project name
project(QmlWebRtcStreamer)

# Set C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic processing for Qt's MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTORCC ON)

# Make the current directory available for #includes (important for MOC)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# --- Add compile definitions to solve conflicts/warnings ---
# This prevents Qt from defining 'emit' as a macro, which conflicts with Wt.
add_compile_definitions(QT_NO_KEYWORDS)
# This silences warnings about the GStreamer WebRTC API being unstable.
add_compile_definitions(GST_USE_UNSTABLE_API)


# --- Find packages (combination of both files) ---

# 1. Find the pkg-config tool
find_package(PkgConfig REQUIRED)

# 2. Find Qt5 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick OpenGL Network Multimedia)

# 4. Find GStreamer package
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

# --- Add include directories ---
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GSTREAMER_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
)

# --- Define executable and sources ---
add_executable(qml_webrtc_streamer
    src/main.cpp
    src/StreamingPipeline.cpp
    qml/qml.qrc
    res/res.qrc
    qml/MyPageChangeButton.qml
    qml/PageChangeButton.qml
)

add_custom_command(
    TARGET qml_webrtc_streamer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/qml/video/cci.m4v
        ${CMAKE_BINARY_DIR}
)


# --- Link libraries ---
target_link_libraries(qml_webrtc_streamer PRIVATE
    # Modern Qt5 targets
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::OpenGL
    Qt6::Network
    Qt6::Multimedia

    # GStreamer & GLib libraries
    ${GSTREAMER_LIBRARIES}
    ${GLIB_LIBRARIES}
)
