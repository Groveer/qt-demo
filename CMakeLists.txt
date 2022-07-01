cmake_minimum_required(VERSION 3.16)

project(qt-demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(DFramework REQUIRED)
#pkg_search_module(DFW REQUIRED dframework)

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

#-----------------------------qt-demo--------------------------------

file(GLOB_RECURSE SRCS_DEMO
    "qt-demo/*.h"
    "qt-demo/*.cpp"
)

set(BIN_NAME_DEMO qt-demo)
add_executable(${BIN_NAME_DEMO} ${SRCS_DEMO})

target_include_directories(${BIN_NAME_DEMO} PUBLIC
    Qt5::Core
		${DFramework_INCLUDE_DIRS}
)

target_link_libraries(${BIN_NAME_DEMO} PRIVATE
    Qt5::Core
		${DFramework_LIBRARIES}
)
