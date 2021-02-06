#!/bin/bash

WORKDIR=.

cd $WORKDIR/output

echo Starting c_service...
./c_service 1111 /c_service "C Service Replying: Hello World!"&

echo Starting go_service ...
./go_service 1112 /go_service "Go Service Replying: Hallo Welt"&

echo Starting python_service ...
./python_service.py 1113 /python_service "Python Service Replying: salve Orbis Terrarum"&

echo Starting ruby_service ...
./ruby_service.rb 1114 /ruby_service "Ruby Service Replying: Bonjour le monde"&

echo Starting rust_service ...
./rust_service 1115 /rust_service "Rust Service Replying: Ciao mondo"&

echo Starting java_service ...
java UDPServer 1116 /java_service "Java Service Replying: Olá Mundo"&

echo Starting Gateway ....
sleep 1
./gateway 1110&

