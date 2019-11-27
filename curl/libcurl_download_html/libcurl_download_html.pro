#-------------------------------------------------
#
# Project created by QtCreator 2016-06-20T11:15:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = libcurl_download_html
TEMPLATE = app

LIBS+="lib/libcurl.dll"

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
