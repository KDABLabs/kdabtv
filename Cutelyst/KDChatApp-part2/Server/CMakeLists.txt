project(KDChatAppBack)

cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

if(WIN32)
  if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  endif()
endif()

include(FetchContent)

FetchContent_Declare(
  FirebaseAdminQt
  GIT_REPOSITORY https://github.com/cutelyst/FirebaseAdminQt.git
  GIT_TAG        a9db10cdb3c1d6d68d37630fea9abcac8e640219
)
FetchContent_MakeAvailable(FirebaseAdminQt)

find_package(Qt5 COMPONENTS Core Network REQUIRED)
find_package(Cutelyst3Qt5 REQUIRED)
find_package(ASqlQt5 0.50 REQUIRED)

# Auto generate moc files
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE TEMPLATES_SRC root/*)

add_subdirectory(src)
