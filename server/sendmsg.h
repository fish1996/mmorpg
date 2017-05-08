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
	int conn;
	std::thread* thread;
	BlockingQueue<char*>* sendQueue;
    friend void run(Send::message msg);
public:
    sendMsg(BlockingQueue<char*>* q);
    void setConn(int c);
    void start();
};
