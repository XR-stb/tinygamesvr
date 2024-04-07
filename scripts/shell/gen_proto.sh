# pwd
# -Iprotocol/proto/commom
# cpp_out 是相对于当前proto文件的位置
# find protocol/proto/server -name "*.proto" | xargs protoc --cpp_out=protocol/protoconf/server

# protoc 默认在当前目录下搜索 -I 可指定路径搜索
# --cpp_out 是相对于当前运行protoc命令的位置，用于指定生成的cpp代码位置，可用绝对路径

# cd protocol/proto/server && protoc --cpp_out=../../protoconf/server -I. *.proto 
# protoc --cpp_out=/home/tianbaosha/cpp_code/tinygamesvr/protocol/protoconf/server \
#        --proto_path=/home/tianbaosha/cpp_code/tinygamesvr/protocol/proto/server \
#        --proto_path=/home/tianbaosha/cpp_code/tinygamesvr/protocol/proto/common \
#        /home/tianbaosha/cpp_code/tinygamesvr/protocol/proto/server/*.proto
       
#!/bin/bash

# 获取当前脚本的完整路径

cd ../../

SCRIPT_PATH=$(readlink -f "$0")

SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

PROTO_PATH="protocol/proto/server"
RELATIVE_CPP_OUT_PATH="protocol/protoconf/server"

CPP_OUT_PATH="${SCRIPT_DIR}/${RELATIVE_CPP_OUT_PATH}"

echo "Output path: $CPP_OUT_PATH"

PROTOC_CMD="protoc --cpp_out=${CPP_OUT_PATH} --proto_path=${PROTO_PATH}"

# 添加你要编译的.proto文件
PROTOC_CMD="${PROTOC_CMD} ${PROTO_PATH}/*.proto"

# 执行命令
eval $PROTOC_CMD