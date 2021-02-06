package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net"
	"os"
	"strconv"
	"strings"
)

func main() {

	args := os.Args

	port, _ := strconv.Atoi(args[1])
	service := args[2]
	_message := args[3]

	file_content := args[1] + "\t" + service
	err := ioutil.WriteFile("conf/go.conf", []byte(file_content), 0644)
	if err != nil {
		log.Fatal("Cannot create a file")
	}

	conn, err := net.ListenUDP("udp", &net.UDPAddr{
		Port: port,
		IP:   net.ParseIP("0.0.0.0"),
	})
	if err != nil {
		panic(err)
	}

	defer conn.Close()

	for {
		message := make([]byte, 20)
		rlen, remote, err := conn.ReadFromUDP(message[:])
		if err != nil {
			panic(err)
		}

		data := strings.TrimSpace(string(message[:rlen]))
		fmt.Println(data)
		send_data := "Service " + service + " " + _message
		conn.WriteToUDP([]byte(send_data), remote)
	}
}
