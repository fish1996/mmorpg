#ifndef HANDLEMSG_H
#define HANDLEMSG_H

#include "blockingqueue.h"
#include <thread>

class handleMsg
{
private:
    BlockingQueue<char*>* queue;
public:
    handleMsg(BlockingQueue<char*>* q);
    void run();
};

#endif // HANDLEMSG_H
