#include "playerMsg.h"

void AllPlayer::add(QString name,Player player)
{
    QMap<QString,PlayerQueue>::iterator it;
    it = map.find(name);
    if(it==map.end()){
        PlayerQueue queue;
        queue.push(player);
        map.insert(name,queue);
    }
    else{
        it->push(player);
    }
}
