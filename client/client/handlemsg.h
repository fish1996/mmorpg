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
    enum State{
        BEGIN,
        LENGTH,
        POSX,
        POSY,
        DIR,
        INDEX,
        USERNAME,
    };
    Client* client;
    State state;
    BlockingQueue<char*>* queue;
public:
    handlemsg(Client* client);
    void run();
};

#endif // HANDLEMSG_H
