#!/bin/bash

WORKDIR=.

cd $WORKDIR/output

echo Starting c_service...
./c_service 1111 /c_service "C Service Replying..."&

echo Starting go_service ...
./go_service 1112 /go_service "Go Service Replying..."&

echo Starting python_service ...
./python_service.py 1113 /python_service "Python Service Replying..."&

echo Starting ruby_service ...
./ruby_service.rb 1114 /ruby_service "Ruby Service Replying..."&

echo Starting rust_service ...
./rust_service 1115 /rust_service "Rust Service Replying..."&

echo Starting java_service ...
java UDPServer 1116 /java_service "Java Service Replying..."&

