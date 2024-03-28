## Build

### 1. [Ubuntu安装bazel](https://shinley.gitbooks.io/bazel/content/an-zhuang-bazel/zai-ubuntu-shang-an-zhuang-bazel.html)
```shell
echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list

curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -

sudo apt-get update && sudo apt-get install bazel

sudo apt-get upgrade bazel
```

### 2. 编译和运行
```shell
# 将制品输出到--symlink_prefix=build/bazel/
bazel build //servers/gamesvr:gamesvr --symlink_prefix=build/bazel/

bazel run //servers/gamesvr:gamesvr --symlink_prefix=build/bazel/
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
./make.py build gamesvr chatsvr # 编译多个个服务
```