cmake_minimum_required(VERSION 2.8...3.28)

set(CMAKE_CXX_STANDARD 17)

project(tinygamesvr)

include_directories(
    .
    common
)

# 搜索所有头文件和cpp文件，并打印出来
file(GLOB_RECURSE HEADERS "*.h")
message("srcs ${HEADERS}")

file(GLOB_RECURSE SOURCES "*.cpp" "*.cc" "*.c" "*.S")
message("srcs ${SOURCES}")

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)