#include "blockingqueue.h"
#include <thread>
class sendMsg
{
private:
	int conn;
	std::thread* thread;
	BlockingQueue<char*>* sendQueue;
	void run();
public:
    sendMsg(BlockingQueue<char*>* q);
    void setConn(int c);
    void start();
}
