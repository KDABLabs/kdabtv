# MIT License
#
# Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.3)
project(QtDesignerPlugin VERSION 1.0.0 LANGUAGES CXX)

include(GenerateExportHeader)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)
set(CMAKE_SHARED_MODULE_PREFIX "")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(QWAMlib SHARED
    FileSelector.cpp
    ImageViewer.cpp
    ImageViewer.ui
    DateSelectorButton.cpp
    DateSelectorDialog.cpp
)

generate_export_header(QWAMlib)
target_link_libraries(QWAMlib PUBLIC Qt5::Widgets)

add_executable(QWAMApp
    main.cpp
)
target_link_libraries(QWAMApp PRIVATE Qt5::Widgets QWAMlib)



### PLUGIN SPECIFIC STUFF
find_package(Qt5UiPlugin CONFIG REQUIRED)

add_library(QWAMPlugins MODULE QWAMPluginCollection.cpp QWAMPlugin.cpp)
target_link_libraries(QWAMPlugins Qt5::Widgets Qt5::UiPlugin)

target_link_libraries(QWAMPlugins QWAMlib)
