
#ifndef CONNECTTHREAD_H
#define CONNECTTHREAD_H

#include <QThread>
#include"BlockingQueue.h"
class Client;
class connectThread : public QThread
{
    Q_OBJECT
private:
    Client* client;
    BlockingQueue<char*>* queue;
public:
    connectThread(Client* c,BlockingQueue<char*>* q);
protected:
    void run();
signals:
    void connectState(bool);
};

#endif // CONNECTTHREAD_H
