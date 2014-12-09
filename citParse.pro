#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T00:08:13
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = citParse
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editparsedreferences.cpp \
    viewparsedreferences.cpp \
    deleteparsedreferences.cpp \
    editreference.cpp \
    editrefindb.cpp \
    journal.cpp \
    addjournal.cpp \
    addvolume.cpp \
    addissue.cpp \
    parsewizard.cpp \
    addauthor.cpp

HEADERS  += mainwindow.h \
    editparsedreferences.h \
    viewparsedreferences.h \
    deleteparsedreferences.h \
    editreference.h \
    editrefindb.h \
    journal.h \
    addjournal.h \
    addvolume.h \
    addissue.h \
    parsewizard.h \
    addauthor.h

FORMS    += mainwindow.ui \
    editparsedreferences.ui \
    viewparsedreferences.ui \
    deleteparsedreferences.ui \
    editreference.ui \
    editrefindb.ui \
    journal.ui \
    addjournal.ui \
    addvolume.ui \
    addissue.ui \
    parsewizard.ui \
    addauthor.ui

RESOURCES += \
    MyResources.qrc
