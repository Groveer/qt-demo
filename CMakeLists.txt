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

# 设置链接参数，仅需要时链接
set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--as-needed")

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

set(SAFE_COMPILER "-fstack-protector-strong -D_FORTITY_SOURCE=1 -z noexecstack")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SAFE_COMPILER}")
# 若当前编译类型为Debug，则需添加额外参数以方便调试
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")

# 某些平台可能需要手动指定mieee参数，否则会有浮点数精度问题，如sw_64
# 使用方式：cmake -DENABLE_MIEEE
if (DEFINED ENABLE_MIEEE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mieee")
endif()

# 若目标库安装了.cmake文件，则可以直接使用find_package
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

# 若目标库未安装.cmake文件，但是安装了.pc文件，则可以使用pkgconfig
find_package(PkgConfig REQUIRED)
# pkg_check_modules(DtkCore REQUIRED dtkcore)

# GNU 默认
set(UT_COMPILER -fprofile-arcs -ftest-coverage)

# Clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(UT_COMPILER -fprofile-instr-generate -ftest-coverage)
endif()

#--------------------------cpp----------------------

set(CPP_NAME cpp-demo)

# ‘fmt’对应fmt.pc文件，‘FMT’可以看作是一个别名，起别名后就可以用‘FMT_INCLUDE_DIRS’和‘FMT_LIBRARIES’这两个变量了
pkg_check_modules(FMT REQUIRED fmt)

# 建议对不同的模块进行分类，使用通配符最佳
file(GLOB_RECURSE CPP_SRCS
    "src/cpp/*.h"
    "src/cpp/*.cpp"
)

# 生成可执行文件
add_executable(${CPP_NAME}
    ${CPP_SRCS} # 不同模块的文件列表变量在这里使用
)

# 安全编译选项，二进制需使用‘-fPIE’编译参数和‘-pie’链接参数，库需使用‘-fPIC’编译参数，两者之间有冲突不能同时使用，注意区分
target_compile_options(${CPP_NAME} PRIVATE -fPIE)
target_link_options(${CPP_NAME} PRIVATE -pie)

# 这里针对当前二进制定义了一个宏，保存着版本号，方便程序代码中调用，若程序中需要自定义宏变量并且在代码中使用，可参考此方法。
# 注意CMAKE_PROJECT_XXX系列变量，某些属性是cmake帮助提供，但某些属性是12行中project方法设置的，所以这里需要注意变量是否可用。
target_compile_definitions(${CPP_NAME} PRIVATE
    VERSION="${CMAKE_PROJECT_VERSION}"
)

target_include_directories(${CPP_NAME} PUBLIC
    ${FMT_INCLUDE_DIRS}
)

target_link_libraries(${CPP_NAME} PRIVATE
    ${FMT_LIBRARIES}
)

#--------------------------qt----------------------

set(QT_NAME qt-demo)


# 建议对不同的模块进行分类，使用通配符最佳
file(GLOB_RECURSE QT_SRCS
    "src/qt/*.h"
    "src/qt/*.cpp"
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

#--------------------------lib----------------------

set(LIB_NAME lib-demo)

pkg_search_module(RSVG2 REQUIRED librsvg-2.0)

file(GLOB_RECURSE INCLUDE_FILES
    "include/*.h"
)

# 建议对不同的模块进行分类，使用通配符最佳
file(GLOB_RECURSE LIB_SRCS
    "src/lib/*.h"
    "src/lib/*.cpp"
)

# 生成lib库，动态库用SHARED，静态库用STATIC，插件用MODULE
add_library(${LIB_NAME} SHARED
    ${LIB_SRCS} # 不同模块的文件列表变量在这里使用
    ${INCLUDE_FILES}
)

# 只有设置了属性，才会生成带版本号的lib库
set_target_properties(${LIB_NAME} PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
)

# 安全编译选项，二进制需使用‘-fPIE’编译参数和‘-pie’链接参数，库需使用‘-fPIC’编译参数，两者之间有冲突不能同时使用，注意区分
target_compile_options(${LIB_NAME} PRIVATE -fPIC)

target_include_directories(${LIB_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${RSVG2_INCLUDE_DIRS}
)

target_link_libraries(${LIB_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${RSVG2_LIBRARIES}
)

#--------------------------unit test----------------------
# 这里对lib库进行单元测试，其他项目可参考此项目单元测试

include(GoogleTest)
find_package(GTest REQUIRED)

set(TEST_NAME ut-lib-demo)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-access-control -fno-inline -Wno-pmf-conversions")

file(GLOB_RECURSE TEST_FILES
    "tests/*.h"
    "tests/*.cpp"
)

add_executable(${TEST_NAME}
    ${INCLUDE_FILES} #若是对二进制进行测试，需要在此包含要测试的h和cpp文件
    ${TEST_FILES}
)

target_include_directories(${TEST_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
)

target_link_libraries(${TEST_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    ${LIB_NAME} # 若是对库进行测试，可直接在此链接，不需要在上面包含cpp文件
    ${RSVG2_LIBRARIES}
    GTest::gtest_main
    GTest::gtest
    -lpthread
    -lgcov
)

# 这里是针对两种编译器的编译参数差异化进行处理，该编译参数是用来生成单元测试覆盖率
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${TEST_NAME} PRIVATE -fprofile-instr-generate -ftest-coverage)
endif()
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${TEST_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
endif()

enable_testing()

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

