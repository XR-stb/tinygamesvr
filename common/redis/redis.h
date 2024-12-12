#include <cpp_redis/cpp_redis>

#include "common/helper/singleton.h"

namespace PROJ_NS {
class Redis : public Singleton<Redis> {
 public:
  cpp_redis::client& GetClient() {
    if (!connected) {
      throw std::runtime_error("Redis client is not connected.");
    }
    return client;
  }

  Redis() : connected(false) { connect("127.0.0.1", 6379, "123456"); }

  ~Redis() {
    if (connected) {
      client.disconnect();
    }
  }

 private:
  void connect(const std::string& host, std::size_t port, const std::string& password) {
    if (!connected) {
      client.connect(host, port,
                     [this](const std::string& host, std::size_t port,
                            cpp_redis::client::connect_state status) {
                       if (status == cpp_redis::client::connect_state::dropped) {
                         std::cout << "client disconnected from " << host << ":" << port
                                   << std::endl;
                         connected = false;
                       }
                     });

      if (!password.empty()) {
        client.auth(password, [](cpp_redis::reply& reply) {
          if (reply.is_error()) {
            throw std::runtime_error("Authentication failed: " + reply.as_string());
          }
        });
      }

      connected = true;
      std::cout << "Connected to Redis at " << host << ":" << port << std::endl;
    }
  }

  bool connected;
  cpp_redis::client client;
};
}  // namespace PROJ_NS