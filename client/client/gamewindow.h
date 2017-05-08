
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#define GLUT_DISABLE_ATEXIT_HACK
#include <QGLWidget>
#include "gl/gl.h"
#include "gl/glu.h"
#include "gl/glut.h"

class GameWindow : public QGLWidget
{
    Q_OBJECT
private:
public:
protected:
    void initializeGL();
    void resizeGL(int width,int height);
    void paintGL();
};

#endif // GAMEWINDOW_H

