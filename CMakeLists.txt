cmake_minimum_required(VERSION 3.16)

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
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Quick)
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
    Qt5::Core
    Qt5::Widgets
)

target_link_libraries(${BIN_NAME_PLUGIN} PRIVATE
    Qt5::Core
    Qt5::Widgets
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
    Qt5::Core
    Qt5::Quick
)

target_link_libraries(${BIN_NAME_QML} PRIVATE
    Qt5::Core
    Qt5::Quick
)

#-----------------------------kf5-demo--------------------------------
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(KF5 REQUIRED COMPONENTS CoreAddons I18n WidgetsAddons XmlGui TextWidgets)

file(GLOB_RECURSE SRCS_KF5
    "kf5-demo/*.h"
    "kf5-demo/*.cpp"
    "kf5-demo/*.qrc"
)

set(BIN_NAME_KF5 kf5-demo)
add_executable(${BIN_NAME_KF5} ${SRCS_KF5})

target_include_directories(${BIN_NAME_KF5} PUBLIC
    Qt5::Widgets
    KF5::CoreAddons
    KF5::WidgetsAddons
    KF5::I18n
    KF5::XmlGui
    KF5::TextWidgets
)

target_link_libraries(${BIN_NAME_KF5} PRIVATE
    Qt5::Widgets
    KF5::CoreAddons
    KF5::WidgetsAddons
    KF5::I18n
    KF5::XmlGui
    KF5::TextWidgets
)

#-----------------------------dtk-demo--------------------------------
find_package(DtkWidget REQUIRED)

file(GLOB_RECURSE SRCS_DTK
    "dtk-demo/*.h"
    "dtk-demo/*.cpp"
)

set(BIN_NAME_DTK dtk-demo)
add_executable(${BIN_NAME_DTK} ${SRCS_DTK} ${SRCS_UTILS})

target_include_directories(${BIN_NAME_DTK} PUBLIC
    Qt5::Core
    Qt5::Widgets
    ${DtkWidget_INCLUDE_DIRS}
)

target_link_libraries(${BIN_NAME_DTK} PRIVATE
    Qt5::Core
    Qt5::Widgets
    ${DtkWidget_LIBRARIES}
)
