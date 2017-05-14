#ifndef TEXTURE_H
#define TEXTURE_H
#define GLUT_DISABLE_ATEXIT_HACK
#include "GL/GLUT.H"
class texture{
    unsigned char* LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader, unsigned char* backgroundColor);
public:
    void loadTex(int i, char *filename, GLuint* texture);//透明纹理
};

#endif // TEXTURE_H
