#ifndef HANDLEMSG_H
#define HANDLEMSG_H

#include "blockingqueue.h"
#include <thread>

class handleMsg
{
private:
    enum State{
        Begin,
        Instruction,
        Length,
        Data,
    }
    BlockingQueue<char*>* receiveQueue;
public:
    handleMsg(BlockingQueue<char*>* q);
    void run();
};

#endif // HANDLEMSG_H
