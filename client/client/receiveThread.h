#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QThread>
#include "blockingQueue.h"
class Client;
class receiveThread : public QThread
{
    Q_OBJECT
private:
    enum{
        BUFFERSIZE = 1024,
    };
    enum STATE{
        START,
        LENGTH,
        TYPE,
        DATA,
        INSTRUCTION,
    }State;
    Client* client;
    char buffer[BUFFERSIZE];
    BlockingQueue<char*>* queue;
public:
    receiveThread(Client* c,BlockingQueue<char*>* q);
protected:
    void run();
signals:
    void checkState(bool);
};
#endif // RECEIVETHREAD_H
