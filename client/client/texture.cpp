
#define _CRT_SECURE_NO_WARNINGS

#include<windows.h>
#include <qDebug>
#include <QLabel>
#include <QImage>
#include <QGLWidget>
#include"texture.h"
#define BITMAP_ID 0x4D42

//读纹理图片
unsigned char* texture::LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader, unsigned char* backgroundColor)
{

    FILE *filePtr;    // 文件指针
    BITMAPFILEHEADER bitmapFileHeader;    // bitmap文件头
    unsigned char    *bitmapImage;        // bitmap图像数据
    int    imageIdx = 0;        // 图像位置索引

                                // 以“二进制+读”模式打开文件filename
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("file not open\n");
        return NULL;
    }
    // 读入bitmap文件图
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    // 验证是否为bitmap文件
    if (bitmapFileHeader.bfType != BITMAP_ID) {
        fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
        return NULL;
    }
    // 读入bitmap信息头
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
    // 将文件指针移至bitmap数据
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
    // 为装载图像数据创建足够的内存
    bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
    // 验证内存是否创建成功
    if (!bitmapImage) {
        fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
        return NULL;
    }

    // 读入bitmap图像数据
    fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
    // 确认读入成功
    if (bitmapImage == NULL) {
        fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
        return NULL;
    }
    unsigned char*   bitmapData;   // 纹理数据

    bitmapData = new unsigned char[bitmapInfoHeader->biSizeImage / 3 * 4];

    int count = 0;
    qDebug()<<bitmapInfoHeader->biSizeImage;
    //添加alpha通道
    for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
        bitmapData[count] = bitmapImage[imageIdx + 2];
        bitmapData[count + 1] = bitmapImage[imageIdx + 1];
        bitmapData[count + 2] = bitmapImage[imageIdx];
        if (bitmapData[count] == backgroundColor[0]
            && bitmapData[count + 1] == backgroundColor[1]
            && bitmapData[count + 2] == backgroundColor[2]){
            bitmapData[count + 3] = 0;
        }
        else bitmapData[count + 3] = 255;
        count += 4;
    }

    // 关闭bitmap图像文件
    fclose(filePtr);
    return bitmapData;
}


//加载纹理的函数
void texture::loadTex(int i, char *filename, GLuint* texture)
{

    QImage tex, buf;
    if(!buf.load(filename))
    {
        qWarning("Cannot open the image...");
        QImage dummy(128, 128, QImage::Format_RGB32);//当没找到所需打开的图片时，创建一副128*128大小，深度为32位的位图
        dummy.fill(Qt::green);
        buf = dummy;
    }

    QLabel* label = new QLabel();
    label->setPixmap(QPixmap::fromImage(buf));
    label->show();
    tex = QGLWidget::convertToGLFormat(buf);//将Qt图片的格式buf转换成opengl的图片格式tex

    glBindTexture(GL_TEXTURE_2D, texture[i]);//将创建的纹理内存指向的内容绑定到纹理对象GL_TEXTURE_2D上，经过这句代码后，以后对
                                            //GL_TEXTURE_2D的操作的任何操作都同时对应与它所绑定的纹理对象

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//当所显示的纹理比加载进来的纹理小时，采用GL_LINEAR的方法来处理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//当所显示的纹理比加载进来的纹理大时，采用GL_LINEAR的方法来处理
    qDebug()<<"load texture id = "<<texture[i];
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, tex.width(), tex.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, tex.bits());//开始真正创建纹理数据
}
