#!/bin/bash
# cpp_out 是相对于当前proto文件的位置
# protoc 默认在当前目录下搜索 -I 可指定路径搜索
# --cpp_out 是相对于当前运行protoc命令的位置，用于指定生成的cpp代码位置，可用绝对路径
# 生成出来的文件，路径会带上protoc 执行前相对于 proto文件的路径
# 如 有 home/gamesvr/proto/a.proto
# 若在 gamesvr 下执行 protoc 则需要指定proto路径 proto/*.proto 然后指定生成位置为home/gamesvr/proto_gen/
# 则最终生成出来的路径为home/gamesvr/proto_gen/proto/a.pb.cc 等，需要我们一定是在当前proto目录执行protoc命令最好
# 这样就比较容易控制生成的文件位置

# 获取当前sh文件的完整路径
SCRIPT_PATH=$(readlink -f "$0")
# 获取上级目录名
SHELL_DIR=$(dirname "$SCRIPT_PATH")
SCRIPTS_DIR=$(dirname "$SHELL_DIR")
# 获取到工作区路径
WORKSPACE_DIR=$(dirname "$SCRIPTS_DIR")

# protoc 路径
# PROTC_BIN="protoc"
# PROTC_BIN="${WORKSPACE_DIR}/tools/proto/protoc"
PROTC_BIN="${WORKSPACE_DIR}/tools/proto/bin/protoc"
PROTC_GEN_MONGO_BIN="${WORKSPACE_DIR}/tools/proto/bin/protoc_gen_mongo"

# 所有proto的文件路径
PROTO_PATH="protocol/proto/server"

# cpp 文件pb.c/pb.h输出 路径
CPP_OUT_PATH="${WORKSPACE_DIR}/protocol/proto_gen/server"
# 清除 C++ 输出目录下的文件
if [ -d "$CPP_OUT_PATH" ]; then
    echo "Clearing files in $CPP_OUT_PATH"
    rm -rf "${CPP_OUT_PATH:?}"/*
fi

# go 文件pb.go输出 路径
GOLANG_OUT_PATH="${WORKSPACE_DIR}/golang/cloud/proto_gen/server"
# 清除 Go 输出目录下的文件
if [ -d "$GOLANG_OUT_PATH" ]; then
    echo "Clearing files in $GOLANG_OUT_PATH"
    rm -rf "${GOLANG_OUT_PATH:?}"/*
fi

# 检查并创建 CPP 输出路径
if [ ! -d "$CPP_OUT_PATH" ]; then
    echo "CPP Output path does not exist. Creating..."
    mkdir -p "$CPP_OUT_PATH"
fi

# 检查并创建 Golang 输出路径
if [ ! -d "$GOLANG_OUT_PATH" ]; then
    echo "Golang Output path does not exist. Creating..."
    mkdir -p "$GOLANG_OUT_PATH"
fi

# 生成grpc.pb.cc/h
eval "pushd ${WORKSPACE_DIR}/${PROTO_PATH}"
PROTOC_CMD="${PROTC_BIN} --grpc_out=${CPP_OUT_PATH} --plugin=protoc-gen-grpc=$(which grpc_cpp_plugin) *.proto"
eval $PROTOC_CMD
eval "popd"

# 生成pb.xxx
PROTOC_CMD="${PROTC_BIN} --proto_path=${PROTO_PATH} \
            --cpp_out=${CPP_OUT_PATH} \
            --go_out=${GOLANG_OUT_PATH} \
            --go_opt=paths=source_relative \
            --go-grpc_out=${GOLANG_OUT_PATH} \
            --go-grpc_opt=paths=source_relative \
            ${PROTO_PATH}/*.proto"
eval $PROTOC_CMD

# # 生成grpc.pb.go
# # --go-grpc_opt=paths=source_relative 使用相对路径去查找proto
# PROTOC_CMD="${PROTC_BIN} \
#             --go-grpc_out=${GOLANG_OUT_PATH} \
#             --go-grpc_opt=paths=source_relative \
#             ${PROTO_PATH}/*.proto"
# eval $PROTOC_CMD

# gen golang mongodb model and crud interface
# PROTOC_CMD="${PROTC_GEN_MONGO_BIN} --proto_path=googleapis *.proto"
# eval $PROTOC_CMD
