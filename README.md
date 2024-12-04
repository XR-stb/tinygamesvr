## Build

### 1. 安装构建工具
[Ubuntu安装bazel](https://shinley.gitbooks.io/bazel/content/an-zhuang-bazel/zai-ubuntu-shang-an-zhuang-bazel.html)
```shell
echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list

curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -

sudo apt-get update && sudo apt-get install bazel

sudo apt-get upgrade bazel
```

安装cmake
```
sudo apt install cmake
```

安装golang
```
sudo apt install golang-go
go version # go version go1.22.2 linux/amd64

# 若golang版本为1.23及以上 可能会出现：invalid go version '1.22.2': must match format 1.23
# 将go.mod 里面的 go 1.22.2改成 go 1.23
```

准备grpc-cpp环境: https://grpc.io/docs/languages/cpp/quickstart/
```
sudo apt install -y build-essential autoconf libtool pkg-config
cd grpc
mkdir -p cmake/build
pushd cmake/build
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..
make -j 4
make install # permision denied 则使用 sudo make install
```

### 2. 编译和运行（更方便的做法是使用./make.py脚本，见下方）
使用bazel
```shell
# 将制品输出到--symlink_prefix=build/bazel/
bazel build //servers/gamesvr:gamesvr --symlink_prefix=build/bazel/

bazel run //servers/gamesvr:gamesvr --symlink_prefix=build/bazel/
```
使用cmake
```shell
cmake .

make
```
### 3. bazel 构建制品清理
```shell
bazel clean 

rm -rf build/bazel/*
```

## 开发

### Cmake 生成 compile_commands.json
```shell
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=on
```

### ./make.py 脚本使用
先给权限
```shell
chmod +x ./make.py
```

编译
```shell
./make.py build # 编译全部target
./make.py run # 运行全部target

./make.py build gamesvr # 编译单个服务
./make.py build gamesvr chatsvr # 编译多个服务

# cpp target 默认使用cmake编译，使用bazle编译如下
./make.py build gamesvr --with-bazel

# 生成proto代码文件
./make.py genproto
```

### 开发环境配置
1. 安装clangd
```shell
sudo apt install clangd

clangd --version # version >= 14即可
```
2. 安装vscode clangd 插件，卸载vscode 微软 c++ 插件
3. 安装clang-format，包括vscode插件(作者：Xaver Hellauer)
```shell
sudo apt install clang-format
```
4. 代码提示
```shell
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=on
```

5. 配置clang-format

6. golang 下载protoc插件（用于生成proto go代码
see: https://grpc.io/docs/languages/go/quickstart/
```shell 
go install google.golang.org/protobuf/cmd/protoc-gen-go@v1.28
go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@v1.2

vi ~/.bashrc 
export PATH="$PATH:$(go env GOPATH)/bin" # 添加到末尾
source ~/.bashrc
```

7. 安装对应的protoc 版本
```shell
# 如果遇到这个错误
if(NOT "${_PROTOBUF_PROTOC_EXECUTABLE_VERSION}" VERSION_EQUAL "${Protobuf_VERSION}")
    message(WARNING "Protobuf compiler version ${_PROTOBUF_PROTOC_EXECUTABLE_VERSION}"
    " doesn't match library version ${Protobuf_VERSION}")
endif()
点击这个宏，然后去下载对应版本的protoc即可
#if PROTOBUF_VERSION != 5026001
https://github.com/protocolbuffers/protobuf/releases/
其中protoc生成的 xx pb.h 中的版本号是 protoc的版本，由于我们已经安装了grpc，所以根据grpc的版本来安装
点击xx pb.h文件中的这个宏，到grpc安装的那个目录看看版本是多少安装即可


# 本项目使用的是以下版本
wget https://github.com/protocolbuffers/protobuf/releases/download/v29.0/protoc-29.0-linux-x86_64.zip
mv protoc-29.0-linux-x86_64.zip tinygamesvr/tools/proto && cd tinygamesvr/tools/proto
unzip protoc-29.0-linux-x86_64.zip
```

关于protoc 生成golang代码可能遇到的问题
https://stackoverflow.com/questions/57700860/error-protoc-gen-go-program-not-found-or-is-not-executable

8. golang 升级相关
https://ubuntuhandbook.org/index.php/2024/02/how-to-install-go-golang-1-22-in-ubuntu-22-04/

9. bazel 编译grpc 相关报错 (TODO)
```shell
ERROR: no such package '@@bazel_tools//platforms': BUILD file not found in directory 'platforms' of external repository @@bazel_tools. Add a BUILD file to a directory to mark it as a package.
ERROR: /home/tianbaosha/.cache/bazel/_bazel_tianbaosha/ad16b30a9f26716226dff8300c03eaa4/external/io_bazel_rules_go/go/toolchain/BUILD.bazel:8:20: no such package '@@bazel_tools//platforms': BUILD file not found in directory 'platforms' of external repository @@bazel_tools. Add a BUILD file to a directory to mark it as a package. and referenced by '@@io_bazel_rules_go//go/toolchain:linux'
ERROR: /home/tianbaosha/cpp_code/tinygamesvr/servers/gamesvr/BUILD:14:10: Analysis failed
ERROR: Analysis of target '//servers/gamesvr:gamesvr' failed; build aborted
```

10. 编译cpp target 报错：fatal error: google/protobuf/generated_message_table_driven.h: No such file or directory
```
未安装grpc
https://grpc.io/docs/languages/cpp/quickstart/
记得执行到最后的make install
```
11.  undefined reference to `absl::xxxx
同样是grpc 安装有异常，重新完整走一遍安装流程