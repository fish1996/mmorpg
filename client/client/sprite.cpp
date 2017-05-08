
#include"sprite.h"
#include<stdio.h>
sprite::sprite(int _col, int _num, float x, float y, GLuint _texture, int* _index, float _step)
{
    count = count2 = count3 = 0;
    col = _col;
    num = _num;
    pos_x = x;
    pos_y = y;
    texture = _texture;
    dir = front;
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 2; k++) {
                index[i][j][k] = _index[cnt++];
            }
        }
    }
    step = _step;
}
void sprite::drawRect(GLuint texture, int i, int j)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);  //选择纹理texture[status]

    const GLfloat x1 = -0.5, x2 = 0.5;
    const GLfloat y1 = -0.5, y2 = 0.5;
    const GLfloat x = 1.0 / col, y = 1.0 / (num / col);
    const GLfloat point[4][2] = { { x1,y1 },{ x2,y1 },{ x2,y2 },{ x1,y2 } };
    const GLfloat dir[4][2] = { { j*x,1 - (i + 1)*y },{ (j + 1)*x,1 - (i + 1)*y },{ (j + 1)*x ,1 - i*y },{ j*x,1 - i*y } };
    glBegin(GL_QUADS);

    for (int k = 0; k < 4; k++) {
        glTexCoord2fv(dir[k]);
        glVertex2fv(point[k]);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void sprite::drawSprite()
{
    const int step = 800;
    count++;

    if (isStop) {
        if (dir == front) {
            drawRect(texture, index[0][1][0], index[0][1][1]);
        }
        else if (dir == back) {
            drawRect(texture, index[3][1][0], index[3][1][1]);
        }
        else if (dir == left) {
            drawRect(texture, index[1][1][0], index[1][1][1]);
        }
        else if (dir == right) {
            drawRect(texture, index[2][1][0], index[2][1][1]);
        }
    }
    else if (dir == front) {
        if (count <= step) {
            drawRect(texture, index[0][0][0], index[0][0][1]);
        }
        else if (count > step&&count <= step * 2) {
            drawRect(texture, index[0][1][0], index[0][1][1]);
        }
        else if (count > step * 2 && count <= step * 3) {
            drawRect(texture, index[0][2][0], index[0][2][1]);
        }
    }
    else if (dir == back) {
        if (count <= step) {
            drawRect(texture, index[3][0][0], index[3][0][1]);
        }
        else if (count > step && count <= step * 2) {
            drawRect(texture, index[3][1][0], index[3][1][1]);
        }
        else if (count > step * 2 && count <= step * 3) {
            drawRect(texture, index[3][2][0], index[3][2][1]);
        }
    }
    else if (dir == left) {
        if (count <= step) {
            drawRect(texture, index[1][0][0], index[1][0][1]);
        }
        else if (count > step && count <= step * 2) {
            drawRect(texture, index[1][1][0], index[1][1][1]);
        }
        else if (count > step * 2 && count <= step * 3) {
            drawRect(texture, index[1][2][0], index[1][2][1]);
        }
    }
    else if (dir == right) {
        if (count <= step) {
            drawRect(texture, index[2][0][0], index[2][0][1]);
        }
        else if (count > step && count <= step * 2) {
            drawRect(texture, index[2][1][0], index[2][1][1]);
        }
        else if (count > step * 2 && count <= step * 3) {
            drawRect(texture, index[2][2][0], index[2][2][1]);
        }
    }
    if (count%step == 0) {
        if (count2 == count3) {
            if (dir == front) {
                drawRect(texture, index[0][1][0], index[0][1][1]);
            }
            else if (dir == back) {
                drawRect(texture, index[3][1][0], index[3][1][1]);
            }
            else if (dir == left) {
                drawRect(texture, index[1][1][0], index[1][1][1]);
            }
            else if (dir == right) {
                drawRect(texture, index[2][1][0], index[2][1][1]);
            }
            isStop = true;

        }
        count3 = count2;
    }
    if (count == step * 3) {
        count = 0;
    }
}

void sprite::moveFront()
{
    dir = front;
    isStop = false;
}

void sprite::moveBack()
{
    dir = back;
    isStop = false;
}

void sprite::moveLeft()
{
    dir = left;
    isStop = false;
    pos_x -= step;
    if (pos_x < -3.8f)pos_x = -3.8f;
}

void sprite::moveRight()
{
    dir = right;
    isStop = false;
    pos_x +=step;
    if (pos_x > 3.8f)pos_x = 3.8f;
}
