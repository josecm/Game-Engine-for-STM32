#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T13:31:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTGame
TEMPLATE = app


SOURCES += main.cpp\
    gameview.cpp \
    vector.cpp \
    entity.cpp \
    image.cpp \
    controller.cpp \
    testgame.cpp

HEADERS  += \
    gameview.h \
    vector.h \
    entity.h \
    image.h \
    controller.h \
    testgame.h

FORMS    += mainwindow.ui

QMAKE_MAC_SDK = "macosx10.10"
