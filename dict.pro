#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T13:23:36
#
#-------------------------------------------------

QT       += core
QT       += network
#QT       += gui
#QT       += widgets

TARGET = dict
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += /home/jiyuhang/program/jyhsdk/cpp/include
LIBS += -L/home/jiyuhang/program/jyhsdk/cpp/lib
LIBS += -ljyh
