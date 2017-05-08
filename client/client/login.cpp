#include "login.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

Login::Login(BlockingQueue<char*>* q,QWidget *parent)
    : queue(q),QWidget(parent)
{
    Layout();
}

void Login::Layout()
{
    userName = new QLabel(QStringLiteral("用户名"));
    password = new QLabel(QStringLiteral("密码"));;
    userNameLine = new QLineEdit();
    passwordLine = new QLineEdit();
    passwordLine->setEchoMode(QLineEdit::Password);
    loginBtn = new QPushButton(QStringLiteral("登录"));
    registerBtn = new QPushButton(QStringLiteral("注册"));
    vlayout = new QVBoxLayout();
    for(int i=0;i<HMAX;i++){
        hlayout[i] = new QHBoxLayout();
    }

    hlayout[0]->addWidget(userName);
    hlayout[0]->addWidget(userNameLine);
    hlayout[1]->addWidget(password);
    hlayout[1]->addWidget(passwordLine);
    hlayout[2]->addWidget(loginBtn);
    hlayout[2]->addWidget(registerBtn);

    vlayout->addLayout(hlayout[0]);
    vlayout->addLayout(hlayout[1]);
    vlayout->addLayout(hlayout[2]);

    connect(loginBtn,SIGNAL(clicked()),this,SLOT(doLogin()));
    setLayout(vlayout);
}

void Login::doLogin()
{
    int count = 3;
    int len = userNameLine->text().length() + password->text().length() + count + 1;
    char *msg = new char[len];
    msg[0] = BEGINMARK;
    msg[1] = len - 2;
    msg[2] = 1;
    for(int i=0;i<userName->text().length();i++){
        msg[count++] = userName->text().at(i).toLatin1();
    }
    msg[count++] = 128;
    for(int i=0;i<password->text().length();i++){
        msg[count++] = (unsigned char)password->text().at(i).toLatin1();
    }
    queue->Put(msg);
    delete[] msg;
 }

Login::~Login()
{

}
