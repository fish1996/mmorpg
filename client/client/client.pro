#-------------------------------------------------
#
# Project created by QtCreator 2017-05-07T00:10:23
#
#-------------------------------------------------

QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += console
TARGET = client
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        login.cpp \
    client.cpp \
    gamewindow.cpp \
    engine.cpp \
    progressbar.cpp \
    connectThread.cpp \
    tree.cpp \
    object.cpp \
    receiveThread.cpp \
    chooseRole.cpp \
    handlemsg.cpp \
    picture.cpp

HEADERS  += login.h \
    client.h \
    gamewindow.h \
    engine.h \
    progressbar.h \
    connectThread.h \
    blockingQueue.h \
    tree.h \
    object.h \
    receiveThread.h \
    playerMsg.h \
    chooseRole.h \
    handlemsg.h \
    picture.h

RESOURCES += \
    img.qrc
