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
    std::thread* thread;
    BlockingQueue<char*>* receiveQueue;
    void run();
public:
    handleMsg(BlockingQueue<char*>* q);
    void start();
};

#endif // HANDLEMSG_H
