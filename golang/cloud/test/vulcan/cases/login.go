package cases

import (
	pb "cloud/proto_gen/server"
	"cloud/test/vulcan/base"
	"cloud/test/vulcan/utils"
	"context"
	"fmt"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"log"
	"time"
)

type Login struct {
	base.BaseCase
}

func init() {
	caser := &Login{}

	caser.Build(caser)
	base.Register(utils.ExtractFileName(utils.GetFilePath()), caser)
}

func (l *Login) Run() error {
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	conn, err := grpc.DialContext(ctx, "localhost:50051", grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("err: %v\n", err)
		return err
	}
	defer conn.Close()

	ctx, cancel = context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	client := pb.NewLoginServiceClient(conn)
	reply, err := client.Login(
		ctx,
		&pb.CSReqLogin{
			ClientVersion:    0,
			ClientResVersion: 0,
			AccountType:      0,
			AccountName:      "114514",
			Password:         "123456",
			RulerName:        "xiaoran",
			ZoneId:           1,
			IsReConnect:      false,
		},
	)
	if err != nil {
		log.Fatalf("Login failed: %v", err)
	}

	fmt.Printf("loginSucc: %v, time:%v\n", reply.PlayerInfo, time.Unix(reply.ServerTime, 0))
	return nil
}
