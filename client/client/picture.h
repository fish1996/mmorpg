#ifndef PICTURE_H
#define PICTURE_H
#include <QPixmap>

class picture{
public:
    QPixmap* image[96];
    picture(QPixmap* img);
};

#endif // PICTURE_H
