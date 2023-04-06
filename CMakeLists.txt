cmake_minimum_required(VERSION 3.13)

# 如果未定义版本号，则指定版本号
set(VERSION "1.0.0" CACHE STRING "define project version")

project(qt-demo
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/groveer/qt-demo
    DESCRIPTION "qt demo."
    VERSION ${VERSION})

# 生成编译命令，用于支持clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(1)
add_subdirectory(log)
