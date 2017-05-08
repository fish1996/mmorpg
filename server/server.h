#ifndef SERVER_H
#define SERVER_H

#include "handlemsg.h"
#include "sendmsg.h"
#include <fstream>

class server
{
private:
    std::ofstream* out;
    sendMsg* sender;
    handleMsg* handler;
    BlockingQueue<char*>* receiveQueue;
    BlockingQueue<char*>* sendQueue;
public:
    server();
    void start();
};


#endif // SERVER_H
