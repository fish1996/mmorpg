#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "blockingQueue.h"
class QLabel;
class QLineEdit;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;

class Login : public QWidget
{
    Q_OBJECT
private:
    enum{HMAX = 3,
         BEGINMARK = 255,};
    QLabel* userName;
    QLabel* password;
    QLineEdit* userNameLine;
    QLineEdit* passwordLine;
    QPushButton* loginBtn;
    QPushButton* registerBtn;
    QHBoxLayout* hlayout[HMAX];
    QVBoxLayout* vlayout;
    BlockingQueue<char*>* queue;

    void Layout();
private slots:
    void doLogin();
public:
    Login(BlockingQueue<char*>* c,QWidget *parent = 0);
    ~Login();
};

#endif // LOGIN_H
