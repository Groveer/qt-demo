cmake_minimum_required(VERSION 3.6)

set(BIN_NAME QtTest)

project(${BIN_NAME} CXX)

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

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "mips64")
    add_definitions(-DMKGRUB)
    message(${CMAKE_SYSTEM_PROCESSOR})
endif()
#find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

#pkg_search_module(UDisk2 REQUIRED udisks2-qt5)

#include_directories(AFTER ${UDisk2_INCLUDE_DIRS})
#QtTest Project start
add_executable(${BIN_NAME}
  QtTest/main.cpp
)

target_include_directories(${BIN_NAME} PUBLIC
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

target_link_libraries(${BIN_NAME} PRIVATE
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
)

install(TARGETS ${BIN_NAME} DESTINATION bin)
#QtTest Project end