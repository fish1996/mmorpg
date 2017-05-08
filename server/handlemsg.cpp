#include "handlemsg.h"
#include <string>
handleMsg::handleMsg(BlockingQueue<char*>* q)
    :receiveQueue(q)
{
}

void handleMsg::start() 
{
	thread = new std::thread(&run,this);
	thread->detach();
}

void handleMsg::run()
{
    int operation;
    int length;
    int count;
    int loginState;
    State state;
    std::string username;
    std::string password;

    for(;;) {
        char* msg = receiveQueue->Take();
        for(int i = 0;i < strlen(msg); i++) {

            unsigned char ch = (unsigned char)(msg[i] & 0x00ff);
            if(ch == 255 && state == Begin) {
                state = Instruction;
            }
            else if(state == Instruction) {
                state = Length;
                operation = ch;
                if(operation == 0){
                    username = "";
                    password = "";
                }
            }
            else if(state == Length) {
                count = 0;
                state = Data;
                length = ch;
                loginState = 0;
            }
            else if(state == Data) {
                if(count == length) {
                    state == Begin;
                    switch(operation) {
                    case 0:{
                        if(username == "fish1996" &&
                                password="200224223") {
                            // 验证通过
                        }
                        break;
                    }
                    }
                    continue;
                }
                switch(operation) {
                case 0: {
                    if(ch == ' '){
                        loginState = 1;
                    }
                    else if(loginState == 0) {
                        username = username + ch;
                    }
                    else if(loginState == 1){
                        password = password + ch;
                    }
                    break;
                }
                case 1: {
                    break;
                }
                }
                count++;
            }
        }
    }
}
