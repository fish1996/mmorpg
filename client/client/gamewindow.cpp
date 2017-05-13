
#include "gamewindow.h"
#include <qDebug>
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清除颜色缓存和深度缓存
    glLoadIdentity(); //初始化矩阵为单位矩阵
    gluLookAt(0,0,8,0,0,0,
        0, 1, 0);               // 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //设置多边形绘制模式：正反面，填充
    glPushMatrix();
    glColor3f(1,0,0);
    glutSolidCube(0.15f);
    glPopMatrix();
   // glutSwapBuffers();
}
