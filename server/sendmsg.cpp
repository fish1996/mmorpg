//send(conn, buffer, len, 0);
#include "sendmsg.h"
sendMsg::sendMsg(BlockingQueue<char*>* q)
    :sendQueue(q)
{
    	
}

void sendMsg::setConn(int c)
{
	conn = c;
}
    
void sendMsg::run()
{
	for(;;) {
		char* msg = sendQueue->Take();
		send(conn, msg, strlen(msg), 0);
	}
}