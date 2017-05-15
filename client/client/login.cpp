#include "login.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <qDebug>
Login::Login(Client* c,QWidget *parent)
    : client(c),QWidget(parent)
{
    Layout();
}

void Login::Layout()
{
    playermsg = new playerMsg();
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

char* Login::toChar(QString str)
{
    char* ch;
    QByteArray* ba = new QByteArray(str.toLatin1());
    ch = ba->data();
    return ch;
}

void Login::doLogin()
{
    int count = 3;
    int len = userNameLine->text().size() + passwordLine->text().size()+ count + 1;
    char* username = toChar(userNameLine->text());
    char* password = toChar(passwordLine->text());
    playermsg->username = userNameLine->text();
    char *msg = new char[len];
    memset(msg,0,sizeof(msg));
    msg[0] = BEGINMARK;
    msg[1] = (char)(len - 2);
    msg[2] = 1;
    for(int i=0;i<userNameLine->text().size();i++){
        msg[count++] = username[i];
    }
    msg[count++] = ' ';
    for(int i=0;i<passwordLine->text().size();i++){
        msg[count++] = password[i];
    }
   // msg[count] = 0;
//    printf("msg = %s password = %s name = %s\n",msg,password,username);
    client->sendMsg(msg);
   // delete[] msg;
 }

Login::~Login()
{

}
