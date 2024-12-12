project(tests)

# 包含通用的 CMake 设置
include(${CMAKE_SOURCE_DIR}/common/CommonSetup.cmake)

set(TEST_BINARY_DIR "${CMAKE_TESTS_BINARY_DIR}/tests")
file(MAKE_DIRECTORY ${TEST_BINARY_DIR})

# 启动测试
enable_testing()
add_test(NAME test_main COMMAND test_main)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test_main test_main.cpp)
target_link_libraries(test_main gtest gtest_main mongocxx bsoncxx)