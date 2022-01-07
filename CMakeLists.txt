cmake_minimum_required(VERSION 3.13)

project(qt-demo CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
endif ()

find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets Quick REQUIRED)
#pkg_search_module(XCB REQUIRED xcb)

file(GLOB_RECURSE SRCS_UTILS
    "utils/*.h"
    "utils/*.cpp"
)

#-----------------------------qt-plugin--------------------------------

file(GLOB_RECURSE SRCS_PLUGIN
    "qt-plugin/*.h"
    "qt-plugin/*.cpp"
)

set(BIN_NAME_PLUGIN qt-plugin)
add_executable(${BIN_NAME_PLUGIN} ${SRCS_PLUGIN} ${SRCS_UTILS})

target_include_directories(${BIN_NAME_PLUGIN} PUBLIC
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

target_link_libraries(${BIN_NAME_PLUGIN} PRIVATE
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
)

install(TARGETS ${BIN_NAME_PLUGIN} DESTINATION bin)

#-----------------------------qt-qml--------------------------------

file(GLOB_RECURSE SRCS_QML
    "qt-qml/*.h"
    "qt-qml/*.cpp"
    "qt-qml/*.qrc"
)

set(BIN_NAME_QML qt-qml)
add_executable(${BIN_NAME_QML} ${SRCS_QML})

target_include_directories(${BIN_NAME_QML} PUBLIC
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Quick_INCLUDE_DIRS}
)

target_link_libraries(${BIN_NAME_QML} PRIVATE
    ${Qt5Core_LIBRARIES}
    ${Qt5Quick_LIBRARIES}
)