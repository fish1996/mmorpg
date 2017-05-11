//send(conn, buffer, len, 0);
#include "sendmsg.h"
#include <string.h>
#include <sys/socket.h>

sendMsg::sendMsg(BlockingQueue<char*>* sq,BlockingQueue<char*>* rq)
    :sendQueue(sq),receiveQueue(rq)
{
    	
}

void run(Send::message msg)
{
    for(;;) {
        char* data = msg.sendQueue->Take();
        send(msg.conn, data,strlen(data), 0);
    }
}


void sendMsg::start()
{
    Send::message msg;
    msg.conn = conn;
    msg.sendQueue = sendQueue;
    thread = new std::thread(run,msg);
	thread->detach();
}

void sendMsg::setConn(int c)
{
	conn = c;
}
