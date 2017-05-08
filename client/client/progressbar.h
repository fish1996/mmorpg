#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
class QMovie;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;

class progressbar : public QWidget
{
    Q_OBJECT
private:
    enum{
        SIZEW = 400,
        SIZEH = 200,
        VMAX = 1,
        HMAX = 1
    };
    QMovie* waitImage;
    QLabel* waitLabel;
    QLabel* tipLabel;
    QHBoxLayout* hlayout[HMAX];
    QVBoxLayout* vlayout[VMAX];
    void layout();
public:
    progressbar(QWidget* parent = 0);
public slots:
    void isFinish();
};


#endif // PROGRESSBAR_H
