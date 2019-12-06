#-------------------------------------------------
#
# Project created by QtCreator 2016-09-23T16:06:16
#
#-------------------------------------------------

QT       += core gui widgets

CONFIG += c++1z

linux-g++ | linux-g++-64 | linux-g++-32 {
    QMAKE_CXX = g++-7
    QMAKE_CC = gcc-7
    QMAKE_CXXFLAGS += -std=c++17
}

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
    Resources/textresources.qrc \
    Resources/imageresources.qrc
