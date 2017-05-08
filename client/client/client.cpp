﻿#include"client.h"
#include<cstdio>
#include<io.h>
#include<cstring>
#include <qDebug>
#include<fstream>
#pragma comment(lib,"ws2_32.lib")
Client::Client()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int ret;
    //WinSock初始化：
    wVersionRequested = MAKEWORD(2, 2);//希望使用的WinSock DLL的版本
    ret = WSAStartup(wVersionRequested, &wsaData);
    if (ret != 0) {
        printf("WSAStartup() failed!\n");
    }
    //确认WinSock DLL支持版本2.2：
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        WSACleanup();
        printf("Invalid Winsock version!\n");
    }
    isConnect = false;
}

bool Client::connect2Host(const char* hostName)
{
    //创建socket
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket < 0) {
        qDebug()<<"cannot create socket\n";
        return false;
    }
    else qDebug()<<"successfully create socket\n";
    memset(&serverChannel, 0, sizeof(serverChannel));//初始化为0

    serverChannel.sin_family = AF_INET;//channel协议家族AF_INET
    serverChannel.sin_addr.S_un.S_addr = inet_addr(hostName);//地址
    qDebug()<<hostName;
    serverChannel.sin_port = htons(SERVER_PORT);//服务器端口

                                                //建立连接
    serverSocket = connect(clientSocket, (sockaddr*)&serverChannel, sizeof(serverChannel));

    if (serverSocket < 0) {
        qDebug()<<serverSocket<<"cannot connect to the host\n";
        return false;
    }
    else {
        qDebug()<<"successfully connect to the host\n";
        return true;
    }
}

bool Client::sendRequest(char* message)
{
    int r = send(clientSocket, message, strlen(message) + 1, 0);
    if (r == SOCKET_ERROR) {
        qDebug()<<"request failed\n";
        return false;
    }
    else {
        qDebug()<<"request success\n";
        return true;
    }
}

Client::~Client()
{
    if (isConnect) {
        isConnect = false;
        closesocket(clientSocket);
    }
}