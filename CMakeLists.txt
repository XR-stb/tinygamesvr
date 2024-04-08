cmake_minimum_required(VERSION 2.8...3.28)

# CPP 版本
set(CMAKE_CXX_STANDARD 17)

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
message("srcs ${HEADERS}")

file(GLOB_RECURSE SOURCES "*.cpp" "*.cc" "*.c" "*.S")
message("srcs ${SOURCES}")

# add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# 生成compile_commands.json 给clangd做代码索引提示
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(Protobuf_PROTOC_EXECUTABLE "/usr/local/bin/protoc")
# 添加 gRPC 头文件路径
include_directories(${_GRPC_CPP_PLUGIN_INCLUDE_DIRS})

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