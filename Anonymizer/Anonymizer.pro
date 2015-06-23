#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T17:01:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Anonymizer
TEMPLATE = app
win32:DEPENDPATH += dlls
win32:DEPENDPATH += dlls
win32:LIBS += -L..\Anonymizer\dlls -lquazip

unix:LIBS += -L/lib/x86_64-linux-gnu/ -lz

#This doesn't work :/
#win32: $$[QT_INSTALL_PREFIX]/src/3rdparty/zlib
#$$[QT_INSTALL_PREFIX]/src/3rdparty/zlib

win32:RC_ICONS += pixmaps/anon.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    filehandler.cpp \
    medStyleSheetParser.cpp

HEADERS  += mainwindow.h \
    filehandler.h \
    DirMaker.h \
    medStyleSheetParser.h

FORMS    += mainwindow.ui

RESOURCES = \
    anonymiser.qrc

OTHER_FILES += \
    medInria.qss
