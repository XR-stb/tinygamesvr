#include <common/framework/zmq/zmq.hpp>

#include "protocol/proto_gen/server/cs_hello.pb.h"
#include "protocol/proto_gen/server/rpc.pb.h"



void sendMsg(zmq::socket_t& socket) {
  rpc::RpcRequest request;
  request.set_method("GreeterServiceImpl.SayHello");

  pb::CSReqHello grpc_request;
  grpc_request.set_name("world");
  request.set_payload(grpc_request.SerializeAsString());

  std::string request_str = request.SerializeAsString();
  zmq::message_t zmq_request(request_str.size());
  memcpy(zmq_request.data(), request_str.data(), request_str.size());

  socket.send(zmq_request);

  zmq::message_t zmq_response;
  socket.recv(&zmq_response);

  std::string response_str(static_cast<char*>(zmq_response.data()), zmq_response.size());
  rpc::RpcResponse response;
  response.ParseFromString(response_str);

  if (response.code() == 0) {
    pb::CSResHello grpc_reply;
    grpc_reply.ParseFromString(response.payload());
    std::cout << "Received: " << grpc_reply.message() << std::endl;
  } else {
    std::cout << "RPC failed: " << response.message() << std::endl;
  }
}

int main() {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REQ);
  socket.connect("tcp://localhost:5555");
  sendMsg(socket);
  sendMsg(socket);
  return 0;
}