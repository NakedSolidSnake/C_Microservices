#!/usr/bin/python

import sys 
import socket

def main(argv):    
    port = sys.argv[1]
    service_name = sys.argv[2]
    message = sys.argv[3]

    file = open("conf/python.conf", "w")
    file.write(port + "\t" + service_name)
    file.close()

    udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    orig = ('', int(port))
    udp.bind(orig)

    while True:
        msg, client = udp.recvfrom(1024)
        udp.sendto (str(message) + "\n", client)    

if __name__ == "__main__":
    main(sys.argv)