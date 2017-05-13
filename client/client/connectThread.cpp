#include <qDebug>
#include "connectThread.h"
#include "Client.h"
connectThread::connectThread(Client* c,BlockingQueue<char*>* q) : client(c),queue(q)
{

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
