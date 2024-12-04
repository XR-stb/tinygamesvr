package main

import (
	"context"
	"fmt"
	"log"
	"time"

	"google.golang.org/grpc"
	pb "cloud/proto_gen/server"
)

func main() {
	// 连接到 gRPC 服务器
	conn, err := grpc.Dial("localhost:50051", grpc.WithInsecure(), grpc.WithBlock(), grpc.WithTimeout(5*time.Second))
	if err != nil {
		log.Fatalf("did not connect: %v", err)
	}
	defer conn.Close()

	// 创建 Greeter 客户端
	client := pb.NewGreeterClient(conn)

	// 准备请求
	user := "world"
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	// 调用 SayHello 方法
	reply, err := client.SayHello(ctx, &pb.HelloRequest{Name: user})
	if err != nil {
		log.Fatalf("could not greet: %v", err)
	}

	// 打印响应
	fmt.Printf("Greeter received: %s\n", reply.Message)
}