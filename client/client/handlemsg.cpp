#include "handlemsg.h"
#include "client.h"
#include <QSet>
#include <qDebug>
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
     //   qDebug()<<"handlemsg";
        char* msg = client->receiveQueue->Take();
        username = "";
        player p;

        p.posx = (((msg[0]&0x00ff)-1)<<8)+ ((msg[1]&0x00ff)-1);
        p.posy = (((msg[2]&0x00ff)-1)<<8)+ ((msg[3]&0x00ff)-1);

        p.index = msg[4];
        qDebug()<<"posx="<<p.posx<<"posy="<<p.posy<<"index="<<p.index;
        for(int i=0;i<strlen(msg)-5;i++){
            username = username + msg[i+5];
        }

        client->allplayer->set.insert(username);
        client->allplayer->map.insert(username,p);
     //   qDebug()<<"strlen="<<strlen(msg)-5<<"username"<< username;
        delete []msg;
    }
}
