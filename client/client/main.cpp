#include "engine.h"
#include "tree.h"

#include <QApplication>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    Object* obj1 = new Object(1);
    Object* obj2 = new Object(2);
    Object* obj3 = new Object(3);
    Object* obj4 = new Object(4);
    QApplication a(argc, argv);
    quadtree t;

    t.add(1,0,0,obj1);
    t.add(2,1,2,obj2);
    t.add(2,3,1,obj3);
    t.add(3,4,0,obj4);
    t.print();
    engine w;

    w.start();
    return a.exec();
}
