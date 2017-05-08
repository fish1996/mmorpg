#ifndef CLIENT_H
#define CLIENT_H

#include<winsock.h>

class Client
{
private:
    enum {
        SERVER_PORT = 3389,
        BUFFER_SIZE = 4096
    };
    sockaddr_in serverChannel;
    char buffer[BUFFER_SIZE];
    int serverSocket;
    int clientSocket;
    bool isConnect;

public:
    Client();
    ~Client();
    bool sendRequest(char* instruction);
    bool connect2Host(const char* hostName);
};

#endif // CLIENT_H
