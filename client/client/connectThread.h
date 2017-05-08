
#ifndef CONNECTTHREAD_H
#define CONNECTTHREAD_H

#include <QThread>
#include "Client.h"
#include"BlockingQueue.h"

class connectThread : public QThread
{
    Q_OBJECT
private:
    Client* client;
    BlockingQueue<char*>* queue;
public:
    connectThread(BlockingQueue<char*>* q);
protected:
    void run();
signals:
    void connectState(bool);
};

#endif // CONNECTTHREAD_H
