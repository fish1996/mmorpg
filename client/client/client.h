#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include<winsock.h>
#include "BlockingQueue.h"
#include "connectThread.h"
#include "receiveThread.h"
#include "handlemsg.h"
#include "playerMsg.h"
class Client : public QObject
{
    Q_OBJECT
private:
    enum {
        SERVER_PORT = 3389,
        BUFFER_SIZE = 4096
    };
    sockaddr_in serverChannel;
    char buffer[BUFFER_SIZE];
    int serverSocket;

    bool isConnect;
    handlemsg* handleThread;
    connectThread* conThread;
    receiveThread* recvThread;


    BlockingQueue<char*>* sendQueue;
    BlockingQueue<char*>* receiveQueue;

public:
    allPlayer* allplayer;
    int clientSocket;
    Client(allPlayer* allplayer);
    ~Client();
    void sendMsg(char* msg);
    bool sendRequest(char* instruction);
    bool connect2Host(const char* hostName);
private slots:
    void checkState(bool);
    void connectState(bool);
signals:
    void checked(bool);
    void connected(bool);
};

#endif // CLIENT_H
