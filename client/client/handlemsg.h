#ifndef HANDLEMSG_H
#define HANDLEMSG_H
#include <QThread>
#include "blockingQueue.h"
#include "playerMsg.h"
class Client;
class handlemsg : public QThread{
    Q_OBJECT
    // 1 byte : length
    // 2 byte : posx
    // 2 byte : posy
    // 1 byte : dir
    // 1 byte : index
    // ? byte : username
private:
    Client* client;
    BlockingQueue<char*>* queue;
public:
    handlemsg(Client* client);
protected:
    void run();
};

#endif // HANDLEMSG_H
