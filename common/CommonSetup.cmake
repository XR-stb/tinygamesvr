# CommonSetup.cmake

# CPP 版本
set(CMAKE_CXX_STANDARD 17)

# 定义所有源文件和头文件的搜索路径
set(SEARCH_DIRS
    "./"
    "src"
    "${CMAKE_SOURCE_DIR}/protocol/proto_gen/server"
    "${CMAKE_SOURCE_DIR}/common"
)

# 初始化空列表
set(HEADERS "")
set(SOURCES "")

# 搜索所有头文件和源文件
foreach(DIR IN LISTS SEARCH_DIRS)
    file(GLOB_RECURSE HEADER_FILES
         "${DIR}/*.h"
         "${DIR}/*.hpp"
    )
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
# find_package(mongocxx REQUIRED)
# find_package(bsoncxx REQUIRED)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# 添加 gRPC 和 Protobuf 的头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC ${Protobuf_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${gRPC_INCLUDE_DIRS})

# 添加 gRPC 和 Protobuf 的库
target_link_libraries(${PROJECT_NAME} PUBLIC ${Protobuf_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC gRPC::grpc++ gRPC::grpc++_reflection cpp_redis tacopie)

# 添加cpp_redis 所需库
target_link_libraries(${PROJECT_NAME} PUBLIC cpp_redis tacopie)

# 链接 mongocxx 和 bsoncxx 库
target_link_libraries(${PROJECT_NAME} PUBLIC mongocxx bsoncxx)

include(FetchContent)

# 配置 spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.15.0  # 你可以选择最新的稳定版本
)

# 下载和编译spdlog
FetchContent_MakeAvailable(spdlog)

# 链接 spdlog
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

# ZeroMQ
target_link_libraries(${PROJECT_NAME} PUBLIC zmq)