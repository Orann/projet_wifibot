#-------------------------------------------------
#
# Project created by QtCreator 2017-05-18T11:33:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network
QT += webenginewidgets

TARGET = projet_wifibot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpconnection.cpp \
    sensors.cpp

HEADERS  += mainwindow.h \
    tcpconnection.h \
    sensors.h

FORMS    += mainwindow.ui
