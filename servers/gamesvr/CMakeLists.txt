project(gamesvr)

# CPP 版本
set(CMAKE_CXX_STANDARD 17)

# 搜索所有头文件和cpp文件，并打印出来
file(GLOB_RECURSE HEADERS "*.h")
message("srcs ${HEADERS}")

file(GLOB_RECURSE SOURCES "*.cpp" "*.cc" "*.c" "*.S")
message("srcs ${SOURCES}")

# grpc protobuf
find_package(Protobuf 3.12.4 REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# 添加 gRPC 头文件路径
include_directories(${_GRPC_CPP_PLUGIN_INCLUDE_DIRS})

# 添加 gRPC 库路径
link_directories(${_GRPC_CPP_PLUGIN_EXECUTABLE})

# 添加 gRPC 相关的库
# target_link_libraries(
#     ${_GRPC_GRPCPP_UNSECURE}
#     ${_PROTOBUF_LIBPROTOBUF}
#     ${_REFLECTION}
#     ${_GRPC_GRPC++_REFLECTION}
# )

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})