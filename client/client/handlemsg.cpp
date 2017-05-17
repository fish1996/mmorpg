#include "handlemsg.h"

void handlemsg::run()
{
    // 1 byte : length
    // 2 byte : posx
    // 2 byte : posy
    // 1 byte : dir
    // 1 byte : index
    // ? byte : username
    int length;
    int posx;
    int posy;
    int dir;
    int index;
    int count;
    QString username;
    state = LENGTH;
    for(;;){
        char* msg = queue->Take();
        for(int i=0;i<strlen(msg);i++) {
            char ch = msg[i];
            if(state == LENGTH) {
                length = ch;
                count = 0;
                state = POSX;
            }
            else if(state == POSX){
                if(count == 0){
                    posx = ch;
                }
                else if(count == 1){
                    posx = (posx<<8) + ch;
                    state = POSY;
                    count = 0;
                }
                count++;
            }
            else if(state == POSY){

            }
        }
    }
}
