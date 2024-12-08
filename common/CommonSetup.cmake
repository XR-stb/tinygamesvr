# CommonSetup.cmake

# CPP 版本
set(CMAKE_CXX_STANDARD 17)

# 定义源文件和头文件的搜索路径
set(SEARCH_DIRS
    "src"
    "${CMAKE_SOURCE_DIR}/protocol/proto_gen/server"
    "${CMAKE_SOURCE_DIR}/common/framework/server"
)

# 初始化空列表
set(HEADERS "")
set(SOURCES "")

# 搜索所有头文件和源文件
foreach(DIR IN LISTS SEARCH_DIRS)
    file(GLOB_RECURSE HEADER_FILES "${DIR}/*.h")
    file(GLOB_RECURSE SOURCE_FILES
        "${DIR}/*.cpp"
        "${DIR}/*.cc"
        "${DIR}/*.c"
        "${DIR}/*.S"
    )
    list(APPEND HEADERS ${HEADER_FILES})
    list(APPEND SOURCES ${SOURCE_FILES})
endforeach()

# grpc protobuf
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# 添加 gRPC 和 Protobuf 的头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE ${Protobuf_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${gRPC_INCLUDE_DIRS})

# 添加 gRPC 和 Protobuf 的库
target_link_libraries(${PROJECT_NAME} PRIVATE ${Protobuf_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE gRPC::grpc++ gRPC::grpc++_reflection cpp_redis tacopie)

# 添加cpp_redis 所需库
target_link_libraries(${PROJECT_NAME} PRIVATE cpp_redis tacopie)