#ifndef ENGINE_H
#define ENGINE_H
#include "blockingQueue.h"
#include <QObject>
class Client;
class progressbar;
class connectThread;
class Login;
class engine : QObject
{
    Q_OBJECT
private:
    enum STATE{
        UNCONNECTED, // 等待连接
        LOGIN,       // 登录
        CHOOSEROOM,  // 游戏大厅
        QUIT,        // 退出
        CONNECTERR,  // 连接服务器失败
    }State;
    BlockingQueue<char*>* queue;
    progressbar* bar;
    connectThread* cThread;
    Login* login;

    bool doConnect();
    void doLogin();
    void updateState();
public:
    void start();
    engine();
private slots:
    void handleState(bool isConnected);
};

#endif // ENGINE_H
