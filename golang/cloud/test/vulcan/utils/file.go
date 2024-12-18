package utils

import (
	"log"
	"path/filepath"
	"runtime"
	"strings"
)

func GetFilePath() string {
	callStackDeps := 1
	_, file, _, ok := runtime.Caller(callStackDeps)
	if !ok {
		log.Panic("get file name fail")
	}
	return file
}

func ExtractFileName(filePath string) string {
	// Get the base name of the file (e.g., "xxx.go" from "/path/to/xxx.go")
	baseName := filepath.Base(filePath)
	// Remove the ".go" extension
	name := strings.TrimSuffix(baseName, ".go")
	return name
}
