#include "engine.h"
#include <QApplication>
#include <iostream>
#include <string>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    engine w;
    //std::cout << std::to_string((long double)1.321);
    w.start();
    return a.exec();
}
