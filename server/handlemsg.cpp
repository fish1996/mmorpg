#include "handlemsg.h"

handleMsg::handleMsg(BlockingQueue<char*>* q)
    :queue(q)
{
}

void handleMsg::run()
{
    for(;;) {
        char* msg = queue->Take();
        for(int i = 0;i < strlen(msg); i++) {
            unsigned char ch = (unsigned char)(msg[i] & 0x00ff);
            switch(ch){
            case 255:{

            }
            }
        }
    }
}
