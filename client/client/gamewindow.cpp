
#include "gamewindow.h"

void GameWindow::initializeGL()
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glClearColor(0,0,0,1);
}

void GameWindow::resizeGL(int width,int height)
{
    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat whRatio = (GLfloat)width / (GLfloat)height;
    gluPerspective(45.0f, whRatio,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void GameWindow::paintGL()
{
}
