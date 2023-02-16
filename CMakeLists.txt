cmake_minimum_required(VERSION 3.13)

# 如果未定义版本号，则指定版本号
set(VERSION "1.0.0" CACHE STRING "define project version")

project(qt-demo
    LANGUAGES CXX
    HOMEPAGE_URL https://example.com
    DESCRIPTION "qt demo."
    VERSION ${VERSION})

# 定义GNU标准安装目录，使用此定义可兼容不同发行版之间的安装目录差异
include(GNUInstallDirs)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
# 设置为检查C++标准打开，若未设置CMAKE_CXX_STANDARD，则会报错
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 若使用标准C++开发，则不需要以下两行，使用Qt则需要
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 设置包含当前目录，建议头文件的包含写全路径
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 打开所有编译警告，理论上项目中不允许有编译警告
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# 生成编译命令，用于支持clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 若未指定安装前缀，则指定前缀为/usr
# 注意大部分发行版默认会将前缀设置为/usr/local，所以若需要安装到/usr，还需在编译时指定
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

# 若未指定编译类型，则指定为Release，防止某些发行版不指定编译类型
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Debug or Release" FORCE)
endif()

# 若当前编译类型为Debug，则需添加额外参数以方便调试
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")

# 若目标库安装了.cmake文件，则可以直接使用find_package
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

# 若目标库未安装.cmake文件，但是安装了.pc文件，则可以使用pkgconfig
find_package(PkgConfig REQUIRED)
# pkg_check_modules(DtkCore REQUIRED dtkcore)

#--------------------------qt----------------------
set(QT_NAME qt-demo)

# 建议对不同的模块进行分类，使用通配符最佳
file(GLOB_RECURSE QT_SRCS
    "src/*.h"
    "src/*.cpp"
)

# 生成可执行文件
add_executable(${QT_NAME}
    ${QT_SRCS} # 不同模块的文件列表变量在这里使用
)

# 安全编译选项，二进制需使用‘-fPIE’编译参数和‘-pie’链接参数，库需使用‘-fPIC’编译参数，两者之间有冲突不能同时使用，注意区分
target_compile_options(${QT_NAME} PRIVATE -fPIE)
target_link_options(${QT_NAME} PRIVATE -pie)

target_include_directories(${QT_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
)

target_link_libraries(${QT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)

