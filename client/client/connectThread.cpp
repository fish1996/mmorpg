#include <qDebug>
#include "connectThread.h"

connectThread::connectThread(BlockingQueue<char*>* q) : queue(q)
{
    client = new Client();
}

void connectThread::run()
{
    bool state = client->connect2Host("120.25.227.72");
    emit(connectState(state));
    for(;;){
        char* msg = queue->Take();
        printf("send = %s\n",msg);
        client->sendRequest(msg);
    }
}
