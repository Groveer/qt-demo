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
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
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
    Qt6::Core
    Qt6::Widgets
)

target_link_libraries(${BIN_NAME_PLUGIN} PRIVATE
    Qt6::Core
    Qt6::Widgets
)
