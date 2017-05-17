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
// 1 byte : length
// 2 byte : posx
// 2 byte : posy
// 1 byte : dir
// 1 byte : index
// ? byte : username
struct player
{
    int length;
    int posx;
    int posy;
    int dir;
    int index;
};

struct allPlayer
{
    QSet<QString> set;
    QMap<QString,player> map;
};

#endif // PLAYERMSG_H
