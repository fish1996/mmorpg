#include "blockingqueue.h"

class sendMsg
{
private:
	int conn;
	BlockingQueue<char*>* sendQueue;
public:
    sendMsg(BlockingQueue<char*>* q);
    void setConn(int c);
    void run();
}
