project(chatsvr)

# 搜索所有头文件和cpp文件，并打印出来
file(GLOB_RECURSE HEADERS "*.h")
# message("srcs ${HEADERS}")

file(GLOB_RECURSE SOURCES "*.cpp" "*.cc" "*.c" "*.S")
# message("srcs ${SOURCES}")

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})