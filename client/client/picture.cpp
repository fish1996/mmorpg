#include "picture.h"

picture::picture(QPixmap* img)
{
    int width = img->width();
    int height = img->height();
    for(int i=0;i<12;i++){
        for(int j=0;j<8;j++){
            image[i*12+j]=img->copy(i*width,j*height,width,height);
        }
    }
}
