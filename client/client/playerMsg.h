#ifndef PLAYERMSG_H
#define PLAYERMSG_H
#include <QString>
#include <QMap>
#include <QSet>
struct playerMsg
{
    QString username;
    int index;
};

struct Player
{
    int posx;
    int posy;
    int index;
};

class PlayerQueue
{
public:
    int front,back;
    int time;
    Player* player1;
    Player* player2;
    enum{
        MAX = 6,
        TMAX = 40,
    };
    inline PlayerQueue() {
        front = back = 0;
        time = 0;
    }
    Player* player[MAX];
    inline void push(Player* p) {
        front = (front + 1)%MAX;
        player[front] = p;
    }
    inline Player* pop(){
        if(front == back)return nullptr;
        back = (back + 1)%MAX;
        return player[back];
    }
};

struct AllPlayer
{
    QMap<QString,PlayerQueue> map;
    void add(QString,Player*);
};

#endif // PLAYERMSG_H
