package main

import (
	"net"
	"strings"
)

type User struct {
	Name   string
	Addr   string
	C      chan string
	Conn   net.Conn
	server *Server
}

func (this *User) UserListenMessage() {
	for {
		sendMsg, ok := <-this.C
		if !ok {
			return
		}
		this.Conn.Write([]byte(sendMsg + "\n"))
	}

}
func NewUser(conn net.Conn, server *Server) *User {
	userAddr := conn.RemoteAddr().String()
	//new 语法糖:使用 &{} 直接返回结构体指针
	newUser := &User{
		Name:   userAddr,
		Addr:   userAddr,
		C:      make(chan string),
		Conn:   conn,
		server: server,
	}

	go newUser.UserListenMessage()

	return newUser
}
func (u *User) Online() {
	u.server.mapLock.Lock()
	u.server.onlineMap[u.Name] = u
	u.server.mapLock.Unlock()

	u.server.BroadCast(u, "online")
}
func (u *User) Offline() {
	u.server.mapLock.Lock()
	delete(u.server.onlineMap, u.Name)
	u.server.mapLock.Unlock()

	u.server.BroadCast(u, "offline")
}
func (u *User) DoMessage(msg string) {
	if msg == "Who" {
		u.server.mapLock.Lock()
		for _, cli := range u.server.onlineMap {
			msg := "[" + cli.Addr + "]" + cli.Name + ":online...\n"
			u.SendMsgToSelf(msg)
		}
		u.server.mapLock.Unlock()
	} else if len(msg) > 7 && msg[:7] == "rename|" {
		newName := msg[7:]

		u.server.mapLock.Lock()
		_, ok := u.server.onlineMap[newName]
		if ok {
			u.SendMsgToSelf("this is used! Please use another name. ")
		} else {
			delete(u.server.onlineMap, u.Name)
			u.server.onlineMap[newName] = u
			u.Name = newName
			u.SendMsgToSelf("You successfully change you name into " + newName + "\n")
		}
		u.server.mapLock.Unlock()
	} else if len(msg) > 4 && msg[0:3] == "to|" {
		remoteName := strings.Split(msg, "|")[1]
		if remoteName == "" {
			u.SendMsgToSelf("msg format is wrong!\n")
			return
		}
		u.server.mapLock.Lock()
		remoteUser, ok := u.server.onlineMap[remoteName]
		u.server.mapLock.Unlock()
		if !ok {
			u.SendMsgToSelf("this is user is not exist!\n")
			return
		}
		sendMsg := strings.Split(msg, "|")[2]
		remoteUser.SendMsgToSelf(u.Name + " say to you: " + sendMsg + "\n")
	} else {
		u.server.BroadCast(u, msg)
	}
}
func (u *User) SendMsgToSelf(msg string) {
	u.Conn.Write([]byte(msg))
}
