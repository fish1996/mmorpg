#/bin/bash
g++ -g -std=c++11 -lpthread sendmsg.cpp server.cpp handlemsg.cpp main.cpp -o a.out -lpthread