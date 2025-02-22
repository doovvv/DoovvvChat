package main

import (
	"flag"
	"fmt"
	"io"
	"net"
	"os"
)

type Client struct {
	ServerIp   string
	ServerPort int
	Name       string
	Conn       net.Conn
	flag       int
}

func NewClient(serverIp string, serverPort int) *Client {
	newClient := &Client{
		ServerIp:   serverIp,
		ServerPort: serverPort,
		Name:       serverIp,
		flag:       999,
	}

	conn, err := net.Dial("tcp", fmt.Sprintf("%s:%d", serverIp, serverPort))

	if err != nil {
		return nil
	}

	newClient.Conn = conn

	return newClient
}

var serverIp string
var serverPort int

func init() {
	flag.StringVar(&serverIp, "ip", "127.0.0.1", "server ip")
	flag.IntVar(&serverPort, "port", 8888, "server port")
}
func (c *Client) meau() bool {
	fmt.Println("1.私聊模式")
	fmt.Println("2.公聊模式")
	fmt.Println("3.更改用户名")
	fmt.Println("0.退出")

	_, err := fmt.Scanln(&c.flag)

	if err != nil {
		fmt.Println("read error!")
		return false
	}
	if c.flag < 0 || c.flag > 3 {
		fmt.Println("please input number bewteen 0 and 3!")
		return false
	}
	return true
}
func (c *Client) UpdateName() {
	fmt.Println("<<please input your name:")
	_, err := fmt.Scanln(
		&c.Name,
	)
	if err != nil {
		fmt.Println("read err!")
	}
	_, err = c.Conn.Write([]byte("rename|" + c.Name + "\n"))
	if err != nil {
		fmt.Println("update name fail!")
	}
}
func (c *Client) DealMessage() {
	_, err := io.Copy(os.Stdout, c.Conn)
	if err != nil {
		fmt.Println("response err!")
	}
}
func (c *Client) PublicChat() {
	var chatMsg string
	fmt.Println("please input msg(exit:input \"exit\")")
	fmt.Scanln(&chatMsg)

	for chatMsg != "exit" {
		_, err := c.Conn.Write([]byte(chatMsg + "\n"))
		if err != nil {
			fmt.Println("send msg to server err!")
		}

		fmt.Println("please input msg(exit:input \"exit\")")
		fmt.Scanln(&chatMsg)

	}
}
func (c *Client) PrivateChat() {
	var remoteName string
	var chatMsg string
	c.SelectUsers()
	fmt.Println("please choose chat user(exit):")
	fmt.Scanln(&remoteName)
	for remoteName != "exit" {
		fmt.Println()
		fmt.Println("please input msg(exit:input \"exit\")")
		fmt.Scanln(&chatMsg)
		for chatMsg != "exit" {
			sendMsg := "to|" + remoteName + "|" + chatMsg + "\n"
			_, err := c.Conn.Write([]byte(sendMsg))
			if err != nil {
				fmt.Println("send msg to server err!")
			}

			fmt.Println("please input msg(exit:input \"exit\")")
			fmt.Scanln(&chatMsg)

		}

	}

}
func (c *Client) SelectUsers() {
	query := "Who\n"
	_, err := c.Conn.Write([]byte(query))
	if err != nil {
		fmt.Println("query user name fail!")
		return
	}
}
func (c *Client) run() {
	for c.flag != 0 {
		for !c.meau() {
		}

		switch c.flag {
		case 1:
			c.PrivateChat()
			break
		case 2:
			c.PublicChat()
			break
		case 3:
			c.UpdateName()
			break
		}
	}
}
func main() {
	flag.Parse()

	client := NewClient(serverIp, serverPort)
	if client == nil {
		fmt.Printf("client connect server fail!")
		return
	}
	go client.DealMessage()
	fmt.Println("client connect server success!")

	client.run()
}
