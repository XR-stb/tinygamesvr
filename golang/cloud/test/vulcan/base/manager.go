package base

import (
	"sync"
)

type BaseManager struct {
	CaseObjMap map[string]ICase
}

var once sync.Once
var mgr *BaseManager

func GetManager() *BaseManager {
	once.Do(func() {
		mgr = &BaseManager{
			CaseObjMap: make(map[string]ICase),
		}
	})
	return mgr
}

func Register(fileName string, caser ICase) {
	GetManager().CaseObjMap[fileName] = caser
}
