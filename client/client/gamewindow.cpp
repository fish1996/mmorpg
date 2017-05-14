
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
    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++){
            *s[i*3+j] = img->copy(j*width,i*height,width,height);
        }
    }
    cur = s[0];
}

Sprite::Sprite()
{
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

mainWindow::mainWindow(int width,QWidget* p)
    :QWidget(p)
{
    pWidth = width;
    movex = 0;

    resize(WIDTH,HEIGHT);
    pressFlag = false;
    isJump = false;
    timer = new QTimer();
    jumpTimer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateState()));
    connect(jumpTimer,SIGNAL(timeout()),this,SLOT(updateJump()));
    loadImg();
}

void mainWindow::updateJump()
{
    sprite[0]->jump();
    if(sprite[0]->posy>=HEIGHT - 200){
        isJump = false;
        jumpTimer->stop();
        sprite[0]->stopJump();
    }
    update();
}

void mainWindow::updateState()
{
    QSet<int>::iterator it;
    for(it=key.begin();it!=key.end();it++){
        switch(*it){
        case Qt::Key_Right :
            sprite[0]->moveRight();
            break ;
        case Qt::Key_Up :
            sprite[0]->moveBack();
            break ;
        case Qt::Key_Left :
            sprite[0]->moveLeft();
            break ;
        case Qt::Key_Down:
            sprite[0]->moveFront();
            break ;
        }
    }
    update();
}

void mainWindow::loadImg()
{
    for(int i=0;i<NUM;i++){
        sprite[i] = new Sprite();
    }
    sprite[0]->setMoveX(&movex);
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
    sprite[0]->load(img[0]);

}

void mainWindow::keyPressEvent(QKeyEvent *e)
{
    qDebug()<<"isPressed";
    if(isJump){
        return;
    }

    int Key = e->key();
    if(Key==Qt::Key_Space){
        qDebug()<<"press space";
        jumpTimer->start(20);
        sprite[0]->startJump();
        isJump = true;
    }
    else if(Key == Qt::Key_Right||
            Key == Qt::Key_Left||
            Key == Qt::Key_Up||
            Key == Qt::Key_Down){
        key.insert(e->key());
        if(!pressFlag){
         //   sprite[0]->moveInit();
            timer->start(20);
            pressFlag = true;
        }
        update();
    }
   // QWidget::keyPressEvent(event);

}

void mainWindow::keyReleaseEvent(QKeyEvent *e)
{
    key.remove(e->key());
    if(pressFlag == true && key.isEmpty()){
        pressFlag = false;
        timer->stop();
        update();
    }
 //   QWidget::keyReleaseEvent(event);
}

void mainWindow::updateMove(int dir)
{
    static int count = 0;
    if(count == sprite[0]->FRAMENUM){
        count = 0;
        if(dir==0)movex -= sprite[0]->step;
        else movex += sprite[0]->step;
    }
    count++;
}

void mainWindow::paintEvent(QPaintEvent *e)
{
    move(movex,0);

    if(sprite[0]->dir==sprite[0]->Right &&sprite[0]->posx + movex>3.0*pWidth/4){
        sprite[0]->isScrollRight = true;
    }
    else{
        sprite[0]->isScrollRight = false;
    }
    if(movex < 0 && sprite[0]->dir==sprite[0]->Left && sprite[0]->posx + movex<1.0*pWidth/4){
        sprite[0]->isScrollLeft = true;
    }
    else{
        sprite[0]->isScrollLeft = false;
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
    paint.drawText(1.0*sprite[0]->posx,1.0*sprite[0]->posy - 15,"fish1996");
    paint.drawPixmap(1.0*sprite[0]->posx,1.0*sprite[0]->posy,50,50,*sprite[0]->cur);
    paint.drawPixmap(30,HEIGHT-300,200,200,*img[8]);
}

GameWindow::GameWindow(QWidget* parent)
    :QWidget(parent){
    resize(WIDTH,HEIGHT);
    window = new mainWindow(WIDTH,this);
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
