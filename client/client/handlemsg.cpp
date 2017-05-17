#include "handlemsg.h"
#include "client.h"
#include <QSet>
handlemsg::handlemsg(Client* c) : client(c)
{
}

void handlemsg::run()
{
    // 1 byte : length
    // 2 byte : posx
    // 2 byte : posy
    // 1 byte : dir
    // 1 byte : index
    // ? byte : username

    QString username;
    for(;;){
        char* msg = client->receiveQueue->Take();
        int ptr = 0;
        while(ptr < strlen(msg)){
            username = "";
            player p;
            p.length = msg[ptr+0];
            p.posx = ((msg[ptr+1]-1)<<8) + (msg[ptr+2]-1);
            p.posy = ((msg[ptr+3]-1)<<8) + (msg[ptr+4]-1);
            p.dir = msg[ptr+5];
            p.index = msg[ptr+6]-1;
            for(int i=0;i<p.length-6;i++){
                username = username + msg[ptr+i+7];
            }
            ptr += p.length+1;
            client->allplayer->set.insert(username);
            client->allplayer->map.insert(username,p);
        }
    }
}
