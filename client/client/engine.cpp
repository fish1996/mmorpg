#include "engine.h"
#include "progressbar.h"
#include "connectThread.h"
#include "login.h"
#include "gamewindow.h"

#include <qDebug>
engine::engine()
{
    queue = new BlockingQueue<char*>();
}

void engine::start()
{
    State = UNCONNECTED;
    updateState();
}

void engine::doLogin()
{
    login = new Login(queue);
    login->show();
}

bool engine::doConnect()
{
    bar = new progressbar();
    bar->show();
    cThread = new connectThread(queue);
    connect(cThread,SIGNAL(connectState(bool)),this,SLOT(handleState(bool)));
    cThread->start();
    return true;
}

void engine::handleState(bool isConnected)
{
    if(isConnected){
        State = LOGIN;
        bar->close();
    }
    else State = CONNECTERR;
    updateState();
}

void engine::doChooseMap()
{
    gameWindow = new GameWindow();
    gameWindow->show();
}

void engine::updateState()
{
    switch(State){
    case UNCONNECTED:{
        if(doConnect()){
            State = LOGIN;
        }
        else {
            State = QUIT;
        }
        break;
    }
    case LOGIN:{
        doLogin();
        break;
    }
    case CHOOSEMAP:{
        doChooseMap();
        break;
    }
    case CONNECTERR:{

    }
    default:{
        break;
    }
    }
    return;
}
