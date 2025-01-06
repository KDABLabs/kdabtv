cmake_minimum_required(VERSION 3.19)
project(ex-texteditor-cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Core Gui Widgets LinguistTools)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
set(CMAKE_AUTOUIC TRUE)

add_executable(ex-texteditor-cmake
  Editor.cpp
  Editor.ui
  main.cpp
  resources.qrc
)

target_link_libraries(ex-texteditor-cmake Qt6::Core Qt6::Gui Qt6::Widgets)

qt_add_translations(TARGETS ex-texteditor-cmake
                    TS_FILES editor_da.ts
                    TS_FILES editor_en_gb.ts)

set(QT_TRANSLATION_DIR "${Qt6_DIR}/../../../translations")
file(GLOB QT_TRANSLATIONS ${QT_TRANSLATION_DIR}/*.qm)
qt_add_resources(ex-texteditor-cmake "qt-translations"
    PREFIX "/translations"
    BASE ${QT_TRANSLATION_DIR}
    FILES ${QT_TRANSLATIONS})

