#include "receiveThread.h"
#include<winsock.h>
#include <qDebug>
#include "Client.h"
receiveThread::receiveThread(Client* c,BlockingQueue<char*>* q)
    :client(c),queue(q)
{

}

void receiveThread::run()
{
    for(;;){
        qDebug()<<"wait message";
        State = START;
        int length;
        int instruction;
        int count;
        memset(buffer, 0, sizeof(buffer));
        int ret = recv(client->clientSocket, buffer, sizeof(buffer), 0);
        if (ret == SOCKET_ERROR) {
            qDebug()<<"error";
            continue;
        }
        else {
            for(int i=0;i<strlen(buffer);i++){
                if(State == START && buffer[i] == 10) {
                    State = LENGTH;
                }
                else if(State == LENGTH) {
                    length = buffer[i];
                    State = INSTRUCTION;
                }
                else if(State == INSTRUCTION){
                    instruction = buffer[i];
                    switch(instruction){
                    case 20:{
                        emit(checkState(true));
                        State = DATA;
                        continue;
                    }
                    case 21:{
                        emit(checkState(false));
                        State = DATA;
                        continue;
                    }
                    case 22:{
                        State = DATA;
                        break;
                    }
                    }
                    count = 0;
                    State = DATA;
                }
                else if(State == DATA) {
                    switch(instruction){
                    case 22:{
                        // 1 byte : length
                        // 2 byte : posx
                        // 2 byte : posy
                        // 1 byte : dir
                        // 1 byte : index
                        // ? byte : username
                        State = START;
                        char *msg = new char[length-1];
                        strcpy(msg,buffer+i);
                        client->receiveQueue->Put(msg);
                        break;
                    }
                    }

                }
            }
            qDebug()<<"receive";
        }
    }
}
