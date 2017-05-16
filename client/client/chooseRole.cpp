#include "chooseRole.h"
#include <QPainter>
#include <qDebug>
#include <QMouseEvent>
#include <QMessageBox>
void Box::set(int _x,int _y,int _w,int _h)
{
    w = _w;
    h = _h;
    x = _x;
    y = _y;
}

bool Box::inBox(int x0,int y0)
{
    return (x0 > x && x0 < x+w && y0 > y && y0 < y+h);
}

chooseRole::chooseRole(QWidget* parent)
    :QWidget(parent)
{
    isOk = false;
    qDebug()<<"here";
    curindex = -1;
    count = 0;
    img.load(":/image/i1.png");
    int width = 1.0*img.width()/col;
    int height = 1.0*img.height()/row;
    for(int i=0;i<ROLENUM;i++){
        qDebug()<<"role"<<i;
        for(int j=0;j<3;j++){
            int x =( i>=4)?1:0;

            role[i][j] = img.copy((3*(i%4)+j)*width,x*1.0*img.height()/2,width,height);
        }
    }
    timer = new QTimer();
    timer->start(100);
    qDebug()<<"here";
    connect(timer,SIGNAL(timeout()),this,SLOT(updateState()));
    for(int i=0;i<ROLENUM;i++){
        int x =( i>=4)?1:0;
        box[i].set(100+(i%4)*80,100+80*x,50,50);
    }
    chooseBox.set(300,300,50,30);
    qDebug()<<"there";
}

void chooseRole::updateState()
{
    count = (count+1)%3;
    update();
}

chooseRole::~chooseRole()
{
    delete timer;
}

void chooseRole::mousePressEvent(QMouseEvent *e)
{
    int cx = e->pos().x();
    int cy = e->pos().y();
    for(int i=0;i<8;i++){
        if(box[i].inBox(cx,cy)){
            curindex = i;
            return;
        }
    }
    if(chooseBox.inBox(cx,cy)){
        isOk = true;
        return;
    }
    curindex = -1;
}

void chooseRole::paintEvent(QPaintEvent* e)
{
    QPainter paint(this);
    paint.drawText(30,30,QStringLiteral("请选择你想要创建的角色"));
    if(isOk){
        if(curindex == -1){
            isOk = false;
            QMessageBox::critical(NULL, "Error", QStringLiteral("请先选择角色"), QMessageBox::Yes,0);
        }
        else {
            emit(choose(curindex));
            return;
        }
    }
    if(curindex!=-1){
        paint.drawRect(box[curindex].x,box[curindex].y,box[curindex].w,box[curindex].h);
    }
    for(int i=0;i<8;i++){
        int x =( i>=4)?1:0;
        paint.drawPixmap(100+(i%4)*80,100+80*x,50,50,role[i][count]);
    }

    paint.setBrush(QColor(50,50,50));
    paint.setPen(QColor(255,255,255));
    paint.drawRect(chooseBox.x,chooseBox.y,chooseBox.w,chooseBox.h);
    paint.setBrush(QColor(255,255,255));
    paint.drawText(320,320,QStringLiteral("确定"));
}
