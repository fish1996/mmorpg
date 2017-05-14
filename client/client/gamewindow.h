
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#define GLUT_DISABLE_ATEXIT_HACK
#include <QGLWidget>
#include <QPixmap>
#include <QTimer>
#include <QSet>
#include "texture.h"
#include "gl/gl.h"
#include "gl/glu.h"

class Sprite{
public :
    enum{
        row = 8,
        col = 12,
        leftbegin = 3,
        leftend = 5,
        rightbegin = 6,
        rightend = 8,
        frontbegin = 0,
        frontend = 2,
        backbegin = 9,
        backend = 11,
        FRAMENUM = 3,
    };
    enum direction{
        Left,
        Right,
        Front,
        Back,
    }dir;
    void setMoveX(int*);
    bool isScrollRight;
    bool isScrollLeft;
    int time;
    int* movex;
    float acc = 0.1f;
    float vx = 3.0f;
    float vy = -5.0f;
    int count = 0;
    Sprite();
    int frontindex;
    int rightindex;
    int backindex;
    int leftindex;
    int step = 5;
    QPixmap* s[12];
    QPixmap* cur;
    int posx;
    int posy;
    void load(QPixmap* img);
    void startJump();
    void stopJump();
    void moveRight();
    void moveLeft();
    void moveFront();
    void moveBack();
    void moveInit();
    void jump();
};

class mainWindow : public QWidget
{
    Q_OBJECT
private:
    int movex;
    enum{
        WIDTH = 3000,
        HEIGHT = 800,
        IMGNUM = 10,
        NUM = 1,
    };
    QSet<int>key;
    QTimer* timer;
    QTimer* jumpTimer;
    int pWidth;
    QPixmap* img[IMGNUM];
    Sprite* sprite[NUM];
    bool pressFlag;
    bool isJump;
    void updateMove(int dir);
public:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
public:
    mainWindow(int width,QWidget* parent = 0);
    void loadImg();
private slots:
    void updateJump();
    void updateState();
};


class GameWindow : public QWidget
{
    Q_OBJECT
private:
    enum{
        WIDTH = 1000,
        HEIGHT = 800,
    };
    mainWindow* window;
public:
    GameWindow(QWidget* parent = 0);
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
};

#endif // GAMEWINDOW_H

