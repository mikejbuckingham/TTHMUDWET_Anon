#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T17:01:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Anonymizer
TEMPLATE = app

unix:LIBS += -L/lib/x86_64-linux-gnu/ -lz

#This doesn't work :/
#win32: $$[QT_INSTALL_PREFIX]/src/3rdparty/zlib
#$$[QT_INSTALL_PREFIX]/src/3rdparty/zlib

SOURCES += main.cpp\
        mainwindow.cpp \
    filehandler.cpp \
    quazip/JlCompress.cpp \
    quazip/qioapi.cpp \
    quazip/quaadler32.cpp \
    quazip/quacrc32.cpp \
    quazip/quagzipfile.cpp \
    quazip/quaziodevice.cpp \
    quazip/quazip.cpp \
    quazip/quazipdir.cpp \
    quazip/quazipfile.cpp \
    quazip/quazipfileinfo.cpp \
    quazip/quazipnewinfo.cpp \
    quazip/unzip.c \
    quazip/zip.c \
    medStyleSheetParser.cpp

HEADERS  += mainwindow.h \
    filehandler.h \
    DirMaker.h \
    quazip/crypt.h \
    quazip/ioapi.h \
    quazip/JlCompress.h \
    quazip/quaadler32.h \
    quazip/quachecksum32.h \
    quazip/quacrc32.h \
    quazip/quagzipfile.h \
    quazip/quaziodevice.h \
    quazip/quazip.h \
    quazip/quazip_global.h \
    quazip/quazipdir.h \
    quazip/quazipfile.h \
    quazip/quazipfileinfo.h \
    quazip/quazipnewinfo.h \
    quazip/unzip.h \
    quazip/zip.h \
    medStyleSheetParser.h

FORMS    += mainwindow.ui

RESOURCES = anonymiser.qrc

OTHER_FILES += \
    medInria.qss
