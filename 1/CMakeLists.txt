cmake_minimum_required(VERSION 3.13)

project(qt-demo LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
# 设置为检查C++标准打开，若未设置CMAKE_CXX_STANDARD，则会报错
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 若使用标准C++开发，则不需要以下两行，使用Qt则需要
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 若未指定编译类型，则指定为Release，防止某些发行版不指定编译类型
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Debug or Release" FORCE)
endif()

# 若当前编译类型为Debug，则需添加额外参数以方便调试
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")

# 若目标库安装了.cmake文件，则可以直接使用find_package
find_package(Qt6 REQUIRED COMPONENTS Core)

#--------------------------qt----------------------
set(QT_NAME qt-demo)

# 建议对不同的模块进行分类，使用通配符最佳
file(GLOB_RECURSE QT_SRCS
    "main.cpp"
)

# 生成可执行文件
add_executable(${QT_NAME}
    ${QT_SRCS} # 不同模块的文件列表变量在这里使用
)

target_include_directories(${QT_NAME} PUBLIC
    Qt6::Core
)

target_link_libraries(${QT_NAME} PRIVATE
    Qt6::Core
)


