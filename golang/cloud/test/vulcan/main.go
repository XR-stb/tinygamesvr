package main

import (
	"context"
	"fmt"
	"log"
	"time"

	pb "cloud/proto_gen/server"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

func main() {
	// Create a context with a timeout
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel() // Ensure the context is cancelled to free resources

	// Use DialContext instead of Dial
	conn, err := grpc.DialContext(ctx, "localhost:50051", grpc.WithTransportCredentials(insecure.NewCredentials())) // Use grpc.WithInsecure() if not using TLS
	if err != nil {
		fmt.Printf("err: %v\n", err)
		return
	}
	defer conn.Close()

	// 创建 Greeter 客户端
	client := pb.NewGreeterClient(conn)

	// 准备请求
	user := "world"
	ctx, cancel = context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	// 调用 SayHello 方法
	reply, err := client.SayHello(ctx, &pb.CSReqHello{Name: &user})
	if err != nil {
		log.Fatalf("could not greet: %v", err)
	}

	// 打印响应
	fmt.Printf("Greeter received: %s\n", reply.GetMessage())

	// 调用 SayHello 方法
	msg := "hello every chat"
	res, err := client.SendChat(ctx, &pb.CSReqSendChat{Msg: &msg})
	if err != nil {
		log.Fatalf("could not greet: %v", err)
	}

	// 打印响应
	fmt.Printf("send chat ret: %v\n", res.Ret)
}
