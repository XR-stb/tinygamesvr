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
./make.py build # 编译全部
./make.py build gamesvr # 编译单个服务
./make.py build gamesvr chatsvr # 编译多个服务

# cpp target 默认使用bazel编译，使用cmake编译如下
./make.py build gamesvr --with-cmake
```

### 开发环境配置
1. 安装clangd
```shell
sudo apt install clangd

clangd --version # version >= 14即可
```
2. 安装vscode clangd 插件，卸载vscode 微软 c++ 插件
3. 安装clang-format，包括vscode插件
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
export PATH="$PATH:$(go env GOPATH)/bin"
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
https://github.com/protocolbuffers/protobuf/releases/tag/v3.12.4
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