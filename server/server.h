
#ifndef SERVER_H
#define SERVER_H

#include "handlemsg.h"
#include "sendmsg.h"
#include <fstream>
#include <set>
namespace Timer{
    struct message
    {
        BlockingQueue<char*>* sendQueue;
    };
}


class server
{
private:
    enum{
        BUFFER_SIZE = 1024,
        MYPORT = 12345,
        QUEUE  = 20,
    };
    int server_sockfd;
    int conn;
    std::ofstream out;
    sendMsg* sender;
    handleMsg* handler;
    BlockingQueue<char*>* receiveQueue;
    BlockingQueue<char*>* sendQueue;
    std::set<int> playerSet;
    friend void broadCast(Timer::message msg);
public:
    server();
    void start();
};


#endif // SERVER_H
