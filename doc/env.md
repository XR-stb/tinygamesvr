准备redis server
```
sudo apt install redis-server
sudo vi /etc/redis/redis.conf
搜索 # requirepass foobared 取消注释 并将 foobared 改成你的密码
sudo systemctl start redis-server
sudo systemctl restart redis-server # 修改密码后需restart
sudo systemctl status redis-server # 查看redis status
sudo systemctl enable redis-server # 设置开机自启

redis-cli # 终端访问
auth 123456 # 密码设置为123456，所以用这个密码登录
```

准备cpp-redis环境
```
cd third_party/cpp-redis
mkdir build && cd build
cmake ..
make
sudo make install

# make 时出现报错：third_party/cpp-redis/sources/core/client.cpp:347:21: error: ‘sleep_for’ is not a member of ‘std::this_thread
# 则在该文件内 #include <thread>
```

准备mongoDB社区版环境
```
# 安装mongoDB到ubuntu
https://www.mongodb.com/zh-cn/docs/manual/tutorial/install-mongodb-on-ubuntu/

# 准备golang驱动
go get go.mongodb.org/mongo-driver/mongo

# 准备C++驱动: https://www.mongodb.com/zh-cn/docs/languages/cpp/cpp-driver/current/installation/linux/
sh scripts/shell/mongo_cpp_diver.sh
```