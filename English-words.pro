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
    config.cpp \
    Words.cpp \
    PushLabel.cpp \
    Controller.cpp \
    Model.cpp \
    AboutView.cpp \
    MainView.cpp \
    SettingsView.cpp

HEADERS  += \
    settings.h \
    config.h \
    Words.h \
    PushLabel.h \
    Controller.h \
    Model.h \
    AboutView.h \
    MainView.h \
    SettingsView.h

FORMS    += \
    settings.ui
