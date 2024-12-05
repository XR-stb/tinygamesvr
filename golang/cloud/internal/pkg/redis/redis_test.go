package redis

import (
	"context"
	"testing"
)

func TestGetRedisClient(t *testing.T) {
	client := GetRedisClient()

	if client == nil {
		t.Fatal("Expected non-nil Redis client")
	}

	ctx := context.Background()

	pong, err := client.Ping(ctx).Result()
	if err != nil {
		t.Fatalf("Failed to connect to Redis: %v", err)
	}

	if pong != "PONG" {
		t.Fatalf("Expected PONG, got %s", pong)
	}

	key := "test_key"
	value := "test_value"
	err = client.Set(ctx, key, value, 0).Err() // 0 表示不设置过期时间
	if err != nil {
		t.Fatalf("Failed to set key %s: %v", key, err)
	}

	retrievedValue, err := client.Get(ctx, key).Result()
	if err != nil {
		t.Fatalf("Failed to get key %s: %v", key, err)
	}

	if retrievedValue != value {
		t.Fatalf("Expected value %s, got %s", value, retrievedValue)
	}

	err = client.Del(ctx, key).Err()
	if err != nil {
		t.Fatalf("Failed to delete key %s: %v", key, err)
	}
}
