#include "progressbar.h"
#include <qDebug>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
progressbar::progressbar(QWidget* parent):
    QWidget(parent)
{
    layout();
}

void progressbar::isFinish()
{
    close();
}

void progressbar::layout()
{
    setFixedSize(SIZEW,SIZEH);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint|Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);

    for(int i=0;i<HMAX;i++) {
        hlayout[i] = new QHBoxLayout();
    }
    for(int i=0;i<VMAX;i++) {
        vlayout[i] = new QVBoxLayout();
    }
    waitImage = new QMovie(":/image/wait.gif");
    waitLabel = new QLabel();
    waitLabel->setMovie(waitImage);
    waitImage->start();

    tipLabel = new QLabel(QStringLiteral("正在连接到服务器"));

    hlayout[0]->addWidget(waitLabel);
    hlayout[0]->addWidget(tipLabel);

    vlayout[0]->addStretch();
    vlayout[0]->addLayout(hlayout[0]);
    vlayout[0]->addStretch();

    setLayout(vlayout[0]);
}

