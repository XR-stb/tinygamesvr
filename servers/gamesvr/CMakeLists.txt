project(gamesvr)

# 包含通用的 CMake 设置
include(${CMAKE_SOURCE_DIR}/common/CommonSetup.cmake)


# Enable AddressSanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")