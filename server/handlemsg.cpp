
#include "handlemsg.h"
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
handleMsg::handleMsg(BlockingQueue<char*>* sq,BlockingQueue<char*>* rq)
    :receiveQueue(rq),sendQueue(sq)
{
}

void run(message msg)
{
    // 2 byte : posx
    // 2 byte : posy
    // 1 byte : dir
    // 1 byte : index
    // ? byte : username
    int operation;
    int length;
    int count;
    int loginState;

    State state;
    char* usermsg;
    std::string username;
    std::string password;
    printf("is running\n");
    std::ofstream out("handle.log");
    for(;;) {
        char* data = msg.receiveQueue->Take();
       // printf("data = %s\n",data);
        printf("total length = %d\n",strlen(data));
        for(int i = 0;i < strlen(data); i++) {
            char ch = data[i];
            printf("ch=%d ",ch);
            if(ch == 10 && state == Begin) {
                printf("begin\n");
                state = Length;
            }
            else if(state == Instruction) {
                printf("instruction\n");
                state = Data;
                operation = ch;
                if(operation == 1){
                    printf("operation = 1\n");
                    username = "";
                    password = "";
                }
                else if(operation == 2){
                    printf("operation = 2\n");
                    usermsg = new char[length+3];
                    usermsg[0] = 10;
                    usermsg[1] = length+1;
                    usermsg[2] = 22;
                    count = 3;
                }
            }
            else if(state == Length) {
                count = 0;
                state = Instruction;
                length = ch;
                loginState = 0;
                printf("length=%d\n",length);
            }
            else if(state == Data) {
                switch(operation) {
                case 1: {
                    if(ch == ' '){
                        loginState = 1;
                    }
                    else if(i==strlen(data)-1){
                        state = Begin;
                        if(username==password) {
                            printf("here ch=%d\n",ch);
                            char* sendData = new char[5];
                            sendData[0] = 10;
                            sendData[1] = 1;
                            sendData[2] = 20;
                            sendData[3] = ch;
                            sendData[4] = 0;
                            msg.sendQueue->Put(sendData);
                            continue;
                        }
                        else {
                            char* sendData = new char[5];
                            sendData[0] = 10;
                            sendData[1] = 1;
                            sendData[2] = 21;
                            sendData[3] = ch;
                            sendData[4] = 0;
                            msg.sendQueue->Put(sendData);
                            continue;
                        }
                    }
                    else if(loginState == 0) {
                        username = username + ch;
                    }
                    else if(loginState == 1){
                        password = password + ch;
                    }
                    count++;
                    break;
                }

                case 2:{
                    if(i==strlen(data) - 1) {
                        usermsg[count] = 0;
                        for(int i=0;i<=count;i++){
                            printf("user msg = %d ",usermsg[i]);
                        }
                        printf("\n");
                        state = Begin;
                        msg.sendQueue->Put(usermsg);

                        continue;
                    }
                    usermsg[count++] = ch;
                    break;
                }
                }
            }
        }
        delete[] data;
    }
}

void handleMsg::start()
{
    message msg;
    msg.receiveQueue = receiveQueue;
    msg.sendQueue = sendQueue;
    thread = new std::thread(run,msg);
    printf("new thread\n");
    //thread->detach();
}
