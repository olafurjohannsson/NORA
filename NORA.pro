#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T17:20:30
#
#-------------------------------------------------

QT       += core gui network xml sql svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NORA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    requestmanager.cpp

HEADERS  += mainwindow.h \
    requestmanager.h

FORMS    += mainwindow.ui

DISTFILES += \
    app.config \
    TODO
