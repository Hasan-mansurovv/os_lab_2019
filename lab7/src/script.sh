#!/bin/bash

pkill server
make
./server 20001 &
sleep 2
./client 127.0.0.1 20001 25