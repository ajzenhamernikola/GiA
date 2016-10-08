#-------------------------------------------------
#
# Project created by QtCreator 2016-09-23T16:06:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GiA
TEMPLATE = app

RC_ICONS += Resources/Icons/GiA.ico

SOURCES += Sources/main.cpp \
    Sources/mainmenu.cpp \
    Sources/node.cpp \
    Sources/edge.cpp \
    Sources/edgevaluetext.cpp \
    Sources/graph.cpp

HEADERS  += Headers/mainmenu.h \
    Headers/node.h \
    Headers/edge.h \
    Headers/edgevaluetext.h \
    Headers/graph.h

FORMS    += Forms/mainmenu.ui

DISTFILES += \
    README.md

RESOURCES += \
    Resources/textresources.qrc
