package redis

import (
	"sync"

	"github.com/redis/go-redis/v9"
)

var once sync.Once
var rdb *redis.Client

func GetRedisClient() *redis.Client {
	once.Do(func() {
		rdb = redis.NewClient(&redis.Options{
			Addr:     "localhost:6379",
			Password: "123456", // no password set
			DB:       0,         // use default DB
		})
	})
	return rdb
}
