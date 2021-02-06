#!/usr/bin/ruby

require 'socket'


port = ARGV[0]
service_name = ARGV[1]
message = ARGV[2]

file = File.new("ruby_service", "w")
if file 
    file.syswrite(service_name.to_s + "\t" + port.to_s)
end

server = UDPSocket.new
server.bind("localhost", port.to_i)

while true
    mesg, addr = server.recvfrom(1024)
    puts mesg
    puts addr    
    server.send message, 0, addr[3], addr[1]
end
