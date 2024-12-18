package cases

import (
	"cloud/test/vulcan/base"
	"cloud/test/vulcan/utils"
	"context"
	"fmt"
	"log"
	"time"

	pb "cloud/proto_gen/server"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

type Greeter struct {
	base.BaseCase
}

func init() {
	caser := &Greeter{}

	caser.Build(caser)
	base.Register(utils.ExtractFileName(utils.GetFilePath()), caser)
}

func (g *Greeter) Run() error {
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	conn, err := grpc.DialContext(ctx, "localhost:50051", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("err: %v\n", err)
		return err
	}
	defer conn.Close()

	client := pb.NewGreeterClient(conn)

	user := "world"
	ctx, cancel = context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	reply, err := client.SayHello(ctx, &pb.CSReqHello{Name: user})
	if err != nil {
		log.Fatalf("could not greet: %v", err)
	}

	fmt.Printf("Greeter received: %s\n", reply.GetMessage())

	msg := "hello every chat"
	res, err := client.SendChat(ctx, &pb.CSReqSendChat{Msg: msg})
	if err != nil {
		log.Fatalf("could not greet: %v", err)
	}

	// 打印响应
	fmt.Printf("send chat ret: %v\n", res.Ret)
	return nil
}
