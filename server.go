package main

import (
	"fmt"
	"io"
	"net"
	"sync"
	"time"
)

type Server struct {
	Ip   string
	Port int

	onlineMap map[string]*User
	mapLock   sync.RWMutex

	Message chan string
}

func NewServer(ip string, port int) *Server {
	server := &Server{
		Ip:        ip,
		Port:      port,
		onlineMap: make(map[string]*User, 5),
		mapLock:   sync.RWMutex{},
		Message:   make(chan string),
	}
	return server
}
func (s *Server) BroadCast(user *User, msg string) {
	sendMsg := "[" + user.Addr + "]" + user.Name + ":" + msg
	s.Message <- sendMsg
}
func (s *Server) ServerListenMessage() {
	for {
		sendMsg := <-s.Message
		s.mapLock.Lock()
		for _, cli := range s.onlineMap {
			cli.C <- sendMsg
		}
		s.mapLock.Unlock()
	}
}
func (s *Server) handler(conn net.Conn) {
	//handle connection,avoid 阻塞 accept
	// newuser
	newUser := NewUser(conn, s)
	//online
	newUser.Online()

	isLive := make(chan bool)

	//accept client msg
	go func() {
		buf := make([]byte, 4096)
		for {
			n, err := conn.Read(buf)
			if n == 0 {
				newUser.Offline()
				return
			}
			if err != nil && err != io.EOF {
				fmt.Println("server accept msg err: ", err)
				return
			}
			msg := string(buf[:n-1])
			newUser.DoMessage(msg)

			isLive <- true
		}
	}()

	fmt.Println("c/s connect success!")

	for {
		select {
		case <-isLive:
		case <-time.After(300 * time.Second):
			{
				newUser.SendMsgToSelf("you are offline\n")
				// newUser.Offline()

				close(newUser.C)

				newUser.Conn.Close()

				return
			}
		}
	}
}
func (this *Server) Start() {
	//sokcet listen
	listener, err := net.Listen("tcp", fmt.Sprintf("%s:%d", this.Ip, this.Port))
	if err != nil {
		fmt.Println("server listen err: ", err)
	}
	//close
	defer listener.Close()

	go this.ServerListenMessage()

	//accept
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("server accecpt err: ", err)
		}
		go this.handler(conn)
	}
}
