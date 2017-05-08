#-------------------------------------------------
#
# Project created by QtCreator 2017-05-07T00:10:23
#
#-------------------------------------------------

QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        login.cpp \
    client.cpp \
    gamewindow.cpp \
    sprite.cpp \
    engine.cpp \
    data.cpp \
    progressbar.cpp \
    connectThread.cpp

HEADERS  += login.h \
    client.h \
    gamewindow.h \
    Sprite.h \
    engine.h \
    data.h \
    progressbar.h \
    connectThread.h \
    blockingQueue.h

RESOURCES += \
    img.qrc
