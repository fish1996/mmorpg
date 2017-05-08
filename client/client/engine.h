#ifndef ENGINE_H
#define ENGINE_H
#include "blockingQueue.h"
#include <QObject>
class Client;
class progressbar;
class connectThread;
class GameWindow;
class Login;
class engine : QObject
{
    Q_OBJECT
private:
    enum STATE{
        UNCONNECTED, // 等待连接
        LOGIN,       // 登录
        CHOOSEMAP,  //  选择地图
        QUIT,        // 退出
        CONNECTERR,  // 连接服务器失败
    }State;
    BlockingQueue<char*>* queue;
    progressbar* bar;
    connectThread* cThread;
    GameWindow* gameWindow;
    Login* login;

    bool doConnect();
    void doLogin();
    void doChooseMap();
    void updateState();
public:
    void start();
    engine();
private slots:
    void handleState(bool isConnected);
};

#endif // ENGINE_H
