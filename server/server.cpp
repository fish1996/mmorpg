﻿#include "server.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define SERVER_NAME "@server_socket"
/*
* Create a UNIX-domain socket address in the Linux "abstract namespace".
*
* The socket code doesn't require null termination on the filename, but
* we do it anyway so string functions work.
*/

using namespace std;

void server::start()
{
    ///定义sockfd
    server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(MYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("bind\n");
    ///bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1) {
        perror("bind error");
        exit(1);
    }

    printf("listen\n");
    ///listen，成功返回0，出错返回-1
    if(listen(server_sockfd,QUEUE) == -1) {
        perror("listen error");
        exit(1);
    }

    ///客户端套接字
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    printf("waiting for connection\n");
    ///成功返回非负描述字，出错返回-1
    while(1){
        conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
        printf("server conn = %d\n",conn);
        sender->setConn(conn);
        if(conn<0) {
            perror("connect error");
            exit(1);
        }
        printf("is connected\n");
        while(1) {
            memset(buffer,0,sizeof(buffer));
            int len = recv(conn, buffer, sizeof(buffer),0);
            char* data = new char[sizeof(buffer)];
            strcpy(data,buffer);
            receiveQueue->Put(data);
            printf("%s\n",buffer);
            if(len<=0)break;
           // send(conn, buffer, len, 0);
        }
        close(conn);
    }
    close(server_sockfd);
}

void broadCast(Timer::message msg)
{
    for(;;){

        sleep(1);
    }
}

server::server()
{
    receiveQueue = new BlockingQueue<char*>();
    sendQueue = new BlockingQueue<char*>();

    handler = new handleMsg(sendQueue,receiveQueue);
    sender = new sendMsg(sendQueue,receiveQueue);
    Timer::message msg;
    msg.sendQueue = sendQueue;
    broadcastThread = new std::thread(broadCast,msg);
    out.open("server.log");


    handler->start();
    sender->start();

}
