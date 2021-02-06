#!/bin/bash

WORKDIR=.
DIRECTORY=output

echo Creating output directory
if [ -d "$DIRECTORY" ]; then
    rm -rf output/*
else
    mkdir output
fi


echo compiling Gateway...
cd $WORKDIR/src/gateway
gcc -o gateway gateway.c
mv gateway ../../output
cd -

echo compiling C Service...
cd $WORKDIR/src/services/c_service
gcc -o c_service service.c 
mv c_service ../../../output
cd -

echo compiling Go Service...
cd $WORKDIR/src/services/go_service
go build -o go_service
mv go_service ../../../output
cd -

echo compiling Python Service...
cd $WORKDIR/src/services/python_service
cp python_service.py ../../../output
cd -

echo compiling Java Service...
cd $WORKDIR/src/services/java_service
javac UDPServer.java
mv UDPServer.class ../../../output
cd -

echo compiling Ruby Service...
cd $WORKDIR/src/services/ruby_service
cp ruby_service.rb ../../../output
cd -

echo compiling Rust Service...
cd $WORKDIR/src/services/rust_service
rustc main.rs -o rust_service
mv rust_service ../../../output
cd -
