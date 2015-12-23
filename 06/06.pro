#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T11:58:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 06
TEMPLATE = app

LIBS+=-L/usr/local/lib

CONFIG += c++14
SOURCES += main.cpp\
        MainWindow.cpp \
    Kek.cpp

HEADERS  += MainWindow.h \
    Kek.h

FORMS    += \
    mainwindow.ui
