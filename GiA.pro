#-------------------------------------------------
#
# Project created by QtCreator 2016-09-23T16:06:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GiA
TEMPLATE = app


SOURCES += Sources/main.cpp \
    Sources/mainmenu.cpp \
    Sources/node.cpp \
    Sources/edge.cpp

HEADERS  += Headers/mainmenu.h \
    Headers/node.h \
    Headers/edge.h

FORMS    += Forms/mainmenu.ui
