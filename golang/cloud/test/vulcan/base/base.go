package base

import "fmt"

type ICase interface {
	Start() error
	Run() error
}

type BaseCase struct {
	caseObj ICase
}

func (c *BaseCase) Build(caseObj ICase) {
	c.caseObj = caseObj
}

func (c *BaseCase) Start() error {
	return c.caseObj.Run()
}

func (c *BaseCase) Run() error {
	fmt.Println("base run")
	return nil
}
