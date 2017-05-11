#ifndef HANDLEMSG_H
#define HANDLEMSG_H

#include "blockingqueue.h"
#include <thread>

enum State{
    Begin,
    Instruction,
    Length,
    Data,
};

struct message
{
    BlockingQueue<char*>* receiveQueue;
};

class handleMsg
{
private:
    std::thread* thread;
    BlockingQueue<char*>* receiveQueue;
    BlockingQueue<char*>* sendQueue;
    friend void run(message msg);
public:
    handleMsg(BlockingQueue<char*>* sq,BlockingQueue<char*>* rq);
    void start();
};

#endif // HANDLEMSG_H
