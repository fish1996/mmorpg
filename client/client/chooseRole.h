#ifndef CHOOSEROLE_H
#define CHOOSEROLE_H

#include <QWidget>
#include <QTimer>

class Box
{
public:
    int x;
    int y;
    int w;
    int h;
    void set(int,int,int,int);
    bool inBox(int,int);
};

class chooseRole : public QWidget{
private:
    Q_OBJECT
    enum {
        ROLENUM = 8,
        row = 8,
        col = 12,
    };
    int curindex;
    int count;
    QTimer* timer;
    Box box[ROLENUM];
    Box chooseBox;
    bool isOk;
    QPixmap img;
    QPixmap role[ROLENUM][3];

public:
    chooseRole(QWidget* parent = 0);
    ~chooseRole();
protected:
    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent *);
private slots:
    void updateState();
signals:
    void choose(int);
};

#endif // CHOOSEROLE_H
