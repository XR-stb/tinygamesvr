project(client)

# CPP 版本
set(CMAKE_CXX_STANDARD 17)

# 搜索所有头文件和cpp文件，并打印出来
file(GLOB_RECURSE HEADERS "*.h" "../../protocol/protoconf/server/*.h")
# message("srcs ${HEADERS}")

file(GLOB_RECURSE SOURCES "*.cpp" "*.cc" "*.c" "*.S" "../../protocol/protoconf/server/*.cc")
# message("srcs ${SOURCES}")

# grpc protobuf
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# 添加 gRPC 和 Protobuf 的头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE ${Protobuf_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${gRPC_INCLUDE_DIRS})

# 添加 gRPC 和 Protobuf 的库
target_link_libraries(${PROJECT_NAME} PRIVATE ${Protobuf_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE gRPC::grpc++ gRPC::grpc++_reflection)