cmake_minimum_required(VERSION 3.10)
project(RangeModel)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
add_executable(RangeModel
	main.cpp
	NormalTableModel.cpp
	SimpleList.cpp
	SimpleTable.cpp
	TableWithHeaders.cpp
	Struct.cpp
	Gadgets.cpp
	Editable.cpp
	Roles.cpp
	Trees.cpp
	TreesOfGadgets.cpp
)
target_link_libraries(RangeModel Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
