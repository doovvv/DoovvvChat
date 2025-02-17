package main

import (
	"fmt"
	"net"
)

type Server struct {
	Ip   string
	Port int
}

func NewServer(ip string, port int) *Server {
	server := &Server{
		Ip:   ip,
		Port: port,
	}
	return server
}
func (this *Server) handler(conn net.Conn) {
	//handle connection,avoid 阻塞 accept
	fmt.Println("c/s connect success!")
}
func (this *Server) Start() {
	//sokcet listen
	listener, err := net.Listen("tcp", fmt.Sprintf("%s:%d", this.Ip, this.Port))
	if err != nil {
		fmt.Println("server listen err: ", err)
	}
	//close
	defer listener.Close()
	//accept
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("server accecpt err: ", err)
		}
		go this.handler(conn)
	}
}
