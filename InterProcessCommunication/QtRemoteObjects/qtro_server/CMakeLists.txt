cmake_minimum_required(VERSION 3.16)

project(qtro_server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core RemoteObjects)

add_executable(qtro_server
  main.cpp
  Sensors.rep
  sensors.h sensors.cpp
)

qt_add_repc_sources(qtro_server Sensors.rep)

target_link_libraries(qtro_server Qt::Core Qt::RemoteObjects)

include(GNUInstallDirs)
install(TARGETS qtro_server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
