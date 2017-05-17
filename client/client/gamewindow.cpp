
#include "gamewindow.h"
#include <QKeyEvent>
#include <qDebug>
#include <QMessageBox>

void Sprite::load(QPixmap* img)
{
    posx = 0;
    posy = 400;
    int width = 1.0*img->width()/col;
    int height = 1.0*img->height()/row;
    for(int i=0;i<12;i++){
        s[i] = new QPixmap();
    }
    int offw = (index%4)*3*width;
    int offh = 4*height*(index>=4);
    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++){
            *s[i*3+j] = img->copy(j*width+offw,offh+i*height,width,height);
        }
    }
    cur = s[0];
}

Sprite::Sprite(int i)
{
    index = i;
    isScrollLeft = false;
    isScrollRight = false;
    frontindex = frontbegin;
    rightindex = rightbegin;
    backindex = backbegin;
    leftindex = leftbegin;
}

void Sprite::moveInit()
{
    count = 0;
    frontindex = frontbegin;
    rightindex = rightbegin;
    backindex = backbegin;
    leftindex = leftbegin;
}

void Sprite::setMoveX(int* x)
{
    movex = x;
}

void Sprite::moveRight()
{
    dir = Right;
    posx += step;
    if(isScrollRight){
        *movex -= step;
    }
    cur = s[rightindex];
    count++;
    if(count == FRAMENUM){
        count = 0;
        rightindex += 1;
        if(rightindex > rightend){
            rightindex = rightbegin;
        }
    }
}

void Sprite::moveLeft()
{
    dir = Left;
    posx -= step;
    if(isScrollLeft){
        *movex += step;
    }
    cur = s[leftindex];
    count++;
    if(count == FRAMENUM){
        count = 0;
        leftindex += 1;
        if(leftindex > leftend){
            leftindex = leftbegin;
        }
    }
}

void Sprite::moveFront()
{
    dir = Front;
    posy += step;
    cur = s[frontindex];
    count++;
    if(count == FRAMENUM){
        count = 0;
        frontindex += 1;
        if(frontindex > frontend){
            frontindex = frontbegin;
        }
    }
}

void Sprite::stopJump()
{
    vy = -3;
}

void Sprite::startJump()
{
    count = 0;
    time = 0;
    switch(dir){
    case Front:
        vx = 0;
        break;
    case Back:
        vx = 0;
        break;
    case Left:
        vx = -3;
        break;
    case Right:
        vx = 3;
        break;
    }
}

void Sprite::jump(){
    vy = vy + acc*time;
    posx += vx;
    posy += vy;
    time++;
}

void Sprite::moveBack()
{
    dir = Back;
    posy -= step;
    cur = s[backindex];
    count++;
    if(count == FRAMENUM){
        count = 0;
        backindex += 1;
        if(backindex > backend){
            backindex = backbegin;
        }
    }
}

mainWindow::mainWindow(int width,Client* c,playerMsg* msg,QWidget* p)
    :QWidget(p)
{

    playermsg = msg;
    pWidth = width;
    movex = 0;
    client = c;

    resize(WIDTH,HEIGHT);
    pressFlag = false;
    isJump = false;
    timer = new QTimer();
    jumpTimer = new QTimer();
    sender = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateState()));
    connect(jumpTimer,SIGNAL(timeout()),this,SLOT(updateJump()));
    connect(sender,SIGNAL(timeout()),this,SLOT(sendPlayerMsg()));
    sender->start(500);
    qDebug()<<"before load";
    loadImg();
    qDebug()<<"after load";
}

char* mainWindow::toChar(QString str)
{
    char* ch;
    QByteArray* ba = new QByteArray(str.toLatin1());
    ch = ba->data();
    return ch;
}

void mainWindow::sendPlayerMsg()
{
    char* msg = new char[9 + playermsg->username.size()];
    char* username = toChar(playermsg->username);
    msg[0] = 10;
    msg[1] = 6 + playermsg->username.size();//length
    msg[2] = 2;
    msg[3] = ((sprite->posx>> 8)&0x00ff) + 1;//坐标x
    msg[4] = ((sprite->posx) & 0x00ff) + 1;
    msg[5] = ((sprite->posy >> 8)&0x00ff) + 1;
    msg[6] = ((sprite->posy) & 0x00ff) + 1;
    int row = playermsg->index>=4?4:0;
    int col =  3*(playermsg->index%4);
    switch(sprite->dir){
    case sprite->Left:
        row += 1;
        col += sprite->leftindex%3;
        break;
    case sprite->Right:
        row += 2;
        col += sprite->rightindex%3;
        break;
    case sprite->Front:
        col += sprite->frontindex%3;
        break;
    case sprite->Back:
        row += 3;
        col += sprite->backindex%3;
        break;
    }
    qDebug()<<"posx="<<sprite->posx<<"posy="<<sprite->posy<<"before";
    msg[7] = 12*row + col + 1;
    for(int i=0;i<playermsg->username.size();i++){
        msg[8+i] = username[i];
    }
    msg[8+playermsg->username.size()] = 0;
    client->sendMsg(msg);
}

void mainWindow::updateJump()
{
    sprite->jump();
    if(sprite->posy>=HEIGHT - 200){
        isJump = false;
        jumpTimer->stop();
        sprite->stopJump();
    }
    update();
}

void mainWindow::updateState()
{
    QSet<int>::iterator it;
    for(it=key.begin();it!=key.end();it++){
        switch(*it){
        case Qt::Key_Right :
            sprite->moveRight();
            break ;
        case Qt::Key_Up :
            sprite->moveBack();
            break ;
        case Qt::Key_Left :
            sprite->moveLeft();
            break ;
        case Qt::Key_Down:
            sprite->moveFront();
            break ;
        }
    }
    update();
}

void mainWindow::loadImg()
{
    sprite = new Sprite(playermsg->index);
    sprite->setMoveX(&movex);
    for(int i=0;i<IMGNUM;i++){
        img[i] = new QPixmap();
    }
    img[0]->load(":/image/i1.png");
    img[1]->load(":/image/WalkWay1.png");
    img[2]->load(":/image/WalkWay2.png");
    img[3]->load(":/image/FloatingIsland.png");
    img[4]->load(":/image/WalkWayEndLeft.png");
    img[5]->load(":/image/Cloud1.png");
    img[6]->load(":/image/Sky.png");
    img[7]->load(":/image/Water.jpg");
    img[8]->load(":/image/Plant2.png");
    pic = new picture(img[0]);
    sprite->load(img[0]);
    delete img[0];
}

void mainWindow::keyPressEvent(QKeyEvent *e)
{
    if(isJump){
        return;
    }

    int Key = e->key();
    if(Key==Qt::Key_Space){
        jumpTimer->start(20);
        sprite->startJump();
        isJump = true;
    }
    else if(Key == Qt::Key_Right||
            Key == Qt::Key_Left||
            Key == Qt::Key_Up||
            Key == Qt::Key_Down){
        key.insert(e->key());
        if(!pressFlag){
            timer->start(20);
            pressFlag = true;
        }
        update();
    }
}

void mainWindow::keyReleaseEvent(QKeyEvent *e)
{
    key.remove(e->key());
    if(pressFlag == true && key.isEmpty()){
        pressFlag = false;
        timer->stop();
        update();
    }
}

void mainWindow::updateMove(int dir)
{
    static int count = 0;
    if(count == sprite->FRAMENUM){
        count = 0;
        if(dir==0)movex -= sprite->step;
        else movex += sprite->step;
    }
    count++;
}

void mainWindow::paintEvent(QPaintEvent *e)
{
    move(movex,0);

    if(sprite->dir==sprite->Right &&sprite->posx + movex>3.0*pWidth/4){
        sprite->isScrollRight = true;
    }
    else{
        sprite->isScrollRight = false;
    }
    if(movex < 0 && sprite->dir==sprite->Left && sprite->posx + movex<1.0*pWidth/4){
        sprite->isScrollLeft = true;
    }
    else{
        sprite->isScrollLeft = false;
    }
    QPainter paint(this);
    paint.drawPixmap(0,0,WIDTH,700,*img[6]);
    paint.drawPixmap(0,700,WIDTH,100,*img[7]);
    paint.drawPixmap(0,0,500,150,*img[5]);
    paint.drawPixmap(500,400,150,150,*img[3]);
    paint.drawPixmap(300,300,100,100,*img[3]);
    paint.drawPixmap(600,350,100,100,*img[3]);
    paint.drawPixmap(600,350,100,100,*img[3]);
    for(int i=10;i>=0;i--){
        if(i==1)paint.drawPixmap(30 + i*225,HEIGHT-310,300,300,*img[1]);
        else paint.drawPixmap(30 + i*225,HEIGHT -310,300,300,*img[2]);
    }
    paint.drawPixmap(-50,600,300,150,*img[4]);
    paint.setPen(QColor(220,220,220));
    paint.drawText(1.0*sprite->posx,1.0*sprite->posy - 15,playermsg->username);
    paint.drawPixmap(1.0*sprite->posx,1.0*sprite->posy,50,50,*sprite->cur);
    paint.drawPixmap(30,HEIGHT-300,200,200,*img[8]);
    QSet<QString>::iterator it;
    for(it=client->allplayer->set.begin();it!=client->allplayer->set.end();it++){
        qDebug()<<"draw"<<*it;
        if((*it).compare(playermsg->username)==0)continue;
        if(client->allplayer->map.contains(*it)){
             QMap<QString,player>::iterator itr = client->allplayer->map.find(*it); //找到特定的“键-值”对
             paint.drawPixmap((*itr).posx,(*itr).posy,50,50,*(pic->image[(*itr).index]));
        }

    }
}

GameWindow::GameWindow(Client* client,playerMsg* msg,QWidget* parent)
    :QWidget(parent){
    resize(WIDTH,HEIGHT);
    window = new mainWindow(WIDTH,client,msg,this);
}

void GameWindow::paintEvent(QPaintEvent *)
{

}

void GameWindow::keyPressEvent(QKeyEvent * e)
{
    window->keyPressEvent(e);
}

void GameWindow::keyReleaseEvent(QKeyEvent *e)
{
    window->keyReleaseEvent(e);
}
