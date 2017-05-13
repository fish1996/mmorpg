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
        printf("wait\n");
        char* data = msg.sendQueue->Take();
        printf("isSend\n");
        printf("conn = %d\n",(msg.conn));
        int r = send((msg.conn), data,strlen(data), 0);
        if (r <= 0) {
            printf("request failed\n");
        }
        else {
            printf("request success\n");
        }
        delete[] data;
    }
}


void sendMsg::start()
{
    msg.sendQueue = sendQueue;
}

void sendMsg::setConn(int c)
{
   msg.conn = c;
   thread = new std::thread(run,msg);
   thread->detach();
}
