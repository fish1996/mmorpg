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
    int operation;
    int length;
    int count;
    int loginState;
    State state;
    std::string username;
    std::string password;
    printf("is running\n");
    std::ofstream out("handle.log");
    for(;;) {
        char* data = msg.receiveQueue->Take();
        printf("data = %s\n",data);
        for(int i = 0;i < strlen(data); i++) {
            char ch = data[i];
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
                    else if(loginState == 0) {
                        username = username + ch;
                    }
                    else if(loginState == 1){
                        password = password + ch;
                    }
                    if(count == length - 2){
                        state = Begin;
                        std::cout <<"username = " <<username <<" "<<password;
                        if(username == "fish1996" &&
                                password == "200224223") {
                            printf("correct\n");
                            // 验证通过
                            continue;
                        }
                    }
                    break;
                }
                }
                count++;
            }
        }
        delete data;
    }
}

void handleMsg::start() 
{
    message msg;
    msg.receiveQueue = receiveQueue;
    thread = new std::thread(run,msg);
    printf("new thread\n");
    //thread->detach();
}
