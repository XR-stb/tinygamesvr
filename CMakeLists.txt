cmake_minimum_required(VERSION 2.8...3.28)
# 项目名
# project(tinygamesvr) # 写在这里会报链接错误

set(CMAKE_CXX_STANDARD_REQUIRED ON)
# CPP 版本
set(CMAKE_CXX_STANDARD 17)

find_program(CLANG_COMPILER NAMES clang clang++)
find_program(GCC_COMPILER NAMES gcc g++)

# 优先使用clang, 没有就使用gcc
if(CLANG_COMPILER)
    message(STATUS "Using Clang compiler: ${CLANG_COMPILER}")
    set(CMAKE_C_COMPILER ${CLANG_COMPILER})
    set(CMAKE_CXX_COMPILER ${CLANG_COMPILER})
elseif(GCC_COMPILER)
    message(STATUS "Using GCC compiler: ${GCC_COMPILER}")
    set(CMAKE_C_COMPILER ${GCC_COMPILER})
    set(CMAKE_CXX_COMPILER ${GCC_COMPILER})
else()
    message(FATAL_ERROR "No suitable compiler found. Please install Clang or GCC.")
endif()

# 项目名
project(tinygamesvr)

# 并行构建核数
set(CMAKE_BUILD_PARALLEL_LEVEL 4)

include_directories(
    .
    common
)

# 搜索所有头文件和cpp文件，并打印出来
file(GLOB_RECURSE HEADERS "*.h")
# message("srcs ${HEADERS}")

file(GLOB_RECURSE SOURCES "*.cpp" "*.cc" "*.c" "*.S")
# message("srcs ${SOURCES}")

# add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# 生成compile_commands.json 给clangd做代码索引提示
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置输出目录
set(CMAKE_BINARY_DIR "build/cmake/servers")

# 添加所有服务子目录, 并更改构建文件输出位置
file(GLOB SERVICE_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/servers ${CMAKE_CURRENT_SOURCE_DIR}/servers/*)
foreach(SERVICE_DIR IN LISTS SERVICE_DIRS)
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/servers/${SERVICE_DIR})
        message(${CMAKE_BINARY_DIR}/${SERVICE_DIR}/)
        add_subdirectory(servers/${SERVICE_DIR} ${CMAKE_BINARY_DIR}/${SERVICE_DIR}/)
    endif()
endforeach()