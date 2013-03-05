#-------------------------------------------------
#
# Project created by QtCreator 2013-03-04T17:08:26
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengl-exercise
TEMPLATE = app

QT += opengl glew

SOURCES += main.cpp\
        Graphics\\glwidget.cpp \
    Graphics/glwidget.cpp

HEADERS  += Graphics\\glwidget.h \
    Graphics/glwidget.h

LIBS += -lGLEW
