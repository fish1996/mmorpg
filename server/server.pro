TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    server.cpp \
    handlemsg.cpp \
    sendmsg.cpp

HEADERS += \
    server.h \
    handlemsg.h \
    blockingqueue.h \
    sendmsg.h
LIBS += -lpthread
