#include "picture.h"
#include <qDebug>
#include <QPainter>
picture::picture(QPixmap* img)
{
    int width = 1.0*img->width()/12;
    int height = 1.0*img->height()/8;
    for(int i=0;i<8;i++){
        for(int j=0;j<12;j++){
          //  qDebug()<<i<<j;
            image[12*i+j] = new QPixmap();
            *image[i*12+j]=img->copy(j*width,i*height,width,height);
        }
    }
}

