package main

import (
	"io/ioutil"
	"log"
	"net"
	"os"
	"strconv"
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
		_, remote, err := conn.ReadFromUDP(message[:])
		if err != nil {
			panic(err)
		}

		conn.WriteToUDP([]byte(_message), remote)
	}
}
