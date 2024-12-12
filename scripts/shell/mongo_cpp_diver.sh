#!/bin/bash
# refer: https://www.mongodb.com/zh-cn/docs/languages/cpp/cpp-driver/current/installation/linux/

set -e

# 更新系统并安装必要的构建工具和依赖项
sudo apt update
sudo apt upgrade -y
sudo apt install -y build-essential cmake pkg-config curl

# 安装 C++ 17 polyfill 库（Boost）
sudo apt install -y libboost-all-dev

# 下载并安装 MongoDB C 驱动 (libmongoc 和 libbson)
MONGO_C_DRIVER_VERSION="1.29.0"
curl -OL https://github.com/mongodb/mongo-c-driver/releases/download/$MONGO_C_DRIVER_VERSION/mongo-c-driver-$MONGO_C_DRIVER_VERSION.tar.gz
tar -xzf mongo-c-driver-$MONGO_C_DRIVER_VERSION.tar.gz
cd mongo-c-driver-$MONGO_C_DRIVER_VERSION
mkdir cmake-build
cd cmake-build
cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
make
sudo make install
cd ../..

# 下载并安装 MongoDB C++ 驱动 (mongocxx)
MONGO_CXX_DRIVER_VERSION="r4.0.0"
curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/$MONGO_CXX_DRIVER_VERSION/mongo-cxx-driver-$MONGO_CXX_DRIVER_VERSION.tar.gz
tar -xzf mongo-cxx-driver-$MONGO_CXX_DRIVER_VERSION.tar.gz
cd mongo-cxx-driver-$MONGO_CXX_DRIVER_VERSION/build

# 配置驱动程序
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBSONCXX_POLY_USE_BOOST=1 \
    -DMONGOCXX_OVERRIDE_DEFAULT_INSTALL_PREFIX=/usr/local

# 构建并安装驱动程序
make
sudo make install

# 清理下载的文件
cd ../..
rm -rf mongo-c-driver-$MONGO_C_DRIVER_VERSION*
rm -rf mongo-cxx-driver-$MONGO_CXX_DRIVER_VERSION*

# 方便构建工具直接找到头文件位置
# 强制覆盖 mongocxx 目录
sudo cp -r /usr/local/include/mongocxx/v_noabi/mongocxx/* /usr/local/include/mongocxx/

# 强制覆盖 bsoncxx 目录
sudo cp -r /usr/local/include/bsoncxx/v_noabi/bsoncxx/* /usr/local/include/bsoncxx/

# 删除原始的 v_noabi 目录, 非必要
# sudo rm -rf /usr/local/include/mongocxx/v_noabi
# sudo rm -rf /usr/local/include/bsoncxx/v_noabi

# 确保不会出现：error while loading shared libraries: libmongocxx.so._noabi: cannot open shared object file: No such file or directory
echo 'export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH' >>~/.bashrc
source ~/.bashrc

echo "MongoDB C++ driver (mongocxx) installation completed successfully."
