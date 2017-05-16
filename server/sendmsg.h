#include "blockingqueue.h"
#include <thread>

namespace Send{
    struct message
    {
        BlockingQueue<char*>* sendQueue;
        int conn;
    };
}

class sendMsg
{
private:
    Send::message msg;
	std::thread* thread;
    BlockingQueue<char*>* receiveQueue;
    BlockingQueue<char*>* sendQueue;
    friend void run(Send::message msg);
public:
    sendMsg(BlockingQueue<char*>* sq,BlockingQueue<char*>* rq);
    void setConn(int c);
    void start();
};
