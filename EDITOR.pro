#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T12:13:58
#
#-------------------------------------------------

QT       += core gui opengl sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EDITOR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    theglwidget.cpp \
    keys.cpp \
    circle.cpp \
    dot.cpp \
    cuttedcone.cpp \
    polygon.cpp \
    prism.cpp

HEADERS  += mainwindow.h \
    theglwidget.h \
    keys.h \
    circle.h \
    dot.h \
    cuttedcone.h \
    polygon.h \
    prism.h

FORMS    += mainwindow.ui
