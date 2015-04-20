#-------------------------------------------------
#
# Project created by QtCreator 2014-11-02T23:52:36
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = English-words
TEMPLATE = app


SOURCES += main.cpp\
    settings.cpp \
    about.cpp \
    config.cpp \
    WordsController.cpp \
    Words.cpp

HEADERS  += \
    settings.h \
    about.h \
    config.h \
    WordsController.h \
    Words.h

FORMS    += words.ui \
    settings.ui \
    about.ui
