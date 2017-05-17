#include "engine.h"
#include "progressbar.h"
#include "login.h"
#include "gamewindow.h"
#include <QMessageBox>
#include <qDebug>
engine::engine()
{
    allplayer = new allPlayer();
    client = new Client(allplayer);
    connect(client,SIGNAL(connected(bool)),this,SLOT(handleState(bool)));
    connect(client,SIGNAL(checked(bool)),this,SLOT(checkState(bool)));
}

void engine::start()
{
    State = UNCONNECTED;
    updateState();
}

void engine::checkState(bool isRight)
{
    if(isRight){
        playermsg = login->playermsg;
        login->close();
        delete login;
        State = CHOOSEMAP;
        updateState();
    }
    else {
        QMessageBox::critical(NULL, "Error", QStringLiteral("账号密码错误"), QMessageBox::Yes,0);
    }
}

void engine::doLogin()
{
    qDebug()<<"isLogin";
    login = new Login(client);
    login->show();
}

bool engine::doConnect()
{
    qDebug()<<"show now";
    bar = new progressbar();
    bar->show();
    qDebug()<<"yes show";
    return true;
}

void engine::handleState(bool isConnected)
{
    qDebug()<<"login";
    if(isConnected){
        State = LOGIN;
        bar->close();
        delete bar;
    }
    else State = CONNECTERR;
    updateState();
}

void engine::doChooseMap()
{
    chooserole = new chooseRole();
    chooserole->show();
    connect(chooserole,SIGNAL(choose(int)),this,SLOT(choose(int)));
}

void engine::choose(int index){
    playermsg->index = index;
    chooserole->close();

    gameWindow = new GameWindow(client,playermsg);
    client->handleThread->start();
    //client->recvThread->start();
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
