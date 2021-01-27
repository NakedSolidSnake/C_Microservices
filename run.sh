#!/bin/bash

./gateway  1111&
./service 2222 /service1 'Hello people'&
./service 2223 /service2 'Bonjour'&
./service 2224 /service3 'Hallo Leute'&
./service 2225 /service4 'Bongiorno'&
