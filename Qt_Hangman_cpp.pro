QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_Hangman_cpp
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           hangman.cpp

HEADERS += mainwindow.h \
           hangman.h

FORMS += MainWindow.ui

RESOURCES += resources.qrc
