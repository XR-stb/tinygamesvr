#pragma once

#include <memory>
#include <mutex>

template <typename T>
class Singleton {
 public:
  // 禁止拷贝构造和赋值操作
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  // 获取单例实例的静态方法
  static T& Instance() {
    std::call_once(initInstanceFlag, &Singleton::initSingleton);
    return *instance;
  }

 protected:
  Singleton() = default;
  virtual ~Singleton() = default;

 private:
  static void initSingleton() { instance.reset(new T()); }

  static std::unique_ptr<T> instance;
  static std::once_flag initInstanceFlag;
};

// 初始化静态成员变量
template <typename T>
std::unique_ptr<T> Singleton<T>::instance = nullptr;

template <typename T>
std::once_flag Singleton<T>::initInstanceFlag;
