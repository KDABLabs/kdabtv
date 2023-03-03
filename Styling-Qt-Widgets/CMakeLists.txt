#
# This file is part of the Oxygen2 project.
#
# SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.9)
project(widget-style-oxygen2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 Qt6 CONFIG REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
set(CMAKE_AUTOUIC TRUE)

add_executable(widget-style-oxygen2
  main.cpp
  progressbarstylehelper.cpp
  maindialog.cpp
  colorrepository.cpp
  pushbuttonstylehelper.cpp
  resource.qrc
  checkboxstylehelper.cpp
  maindialog.ui
  teststyle.cpp
  toggleswitch.cpp
)
target_link_libraries(widget-style-oxygen2 Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)
