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
                        //
                        break;
                    }
                    }

                    if(count == length - 1){
                        State = START;
                        continue;
                    }
                    count++;
                }
            }
            qDebug()<<"receive";
        }
    }
}
