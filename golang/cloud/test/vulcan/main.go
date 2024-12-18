package main

import (
	"cloud/test/vulcan/base"
	"flag"
	"log"
)

type Arguments struct {
	CaseName string
}

var args Arguments

func init() {
	flag.StringVar(&args.CaseName, "case", "login", "run case name")

	flag.Parse()
}

func main() {
	caseObj := base.GetManager().CaseObjMap[args.CaseName]
	if caseObj != nil {
		err := caseObj.Start()
		if err != nil {
			log.Panicf("run %v failed", args.CaseName)
			return
		}
	}
}
