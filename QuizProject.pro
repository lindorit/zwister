#-------------------------------------------------
#
# Project created by QtCreator 2024-05-13T22:14:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuizProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myfile.cpp \
    questionswindowone.cpp \
    pugixml.cpp \
    questionswindowtwo.cpp \
    questionswindowthree.cpp \
    reviewwindow.cpp \
    startquizwindow.cpp \
    mainwindowimg.cpp

HEADERS  += mainwindow.h \
    myfile.h \
    questionswindowone.h \
    pugiconfig.hpp \
    pugixml.hpp \
    questionswindowtwo.h \
    questionswindowthree.h \
    reviewwindow.h \
    startquizwindow.h \
    mainwindowimg.h

FORMS    += mainwindow.ui \
    questionswindowone.ui \
    questionswindowtwo.ui \
    questionswindowthree.ui \
    reviewwindow.ui \
    startquizwindow.ui
