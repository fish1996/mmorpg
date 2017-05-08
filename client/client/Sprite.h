#include "gl/GLUT.H"

class sprite
{
private:
    //bool isColl;
    //帧动画参数
    int num;//一共多少帧
    int col;//一行有多少帧

                 //精灵索引下标
                 //前、左、右、后
    int index[4][3][2];

    //步长
    float step;

    //用于计数
    int count;
    int count3;

    //精灵贴图
    GLuint texture;

    //是否停止
    bool isStop = true;

    //快速索引绘制精灵
    void drawRect(GLuint texture, int i, int j);

public:
    //绘制精灵
    void drawSprite();

    //用于计数
    int count2;

    //是否碰撞
    bool isColl = false;

    //行走方向（枚举量）
    typedef enum { left, right, front, back }direction;

    //精灵位置（中心位置）
    float pos_x;
    float pos_y;

    sprite(int _col, int _num, float x, float y, GLuint _texture, int* index, float _step);
    void moveLeft();
    void moveRight();
    void moveFront();
    void moveBack();

    //行走方向
    direction dir;
};
