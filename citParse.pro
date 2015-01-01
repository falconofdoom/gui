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
    editrefindb.cpp \
    journal.cpp \
    addjournal.cpp \
    addvolume.cpp \
    addissue.cpp \
    parsewizard.cpp \
    addauthor.cpp \
    articles.cpp \
    editarticle.cpp \
    parsers.cpp \
    addparser.cpp \
    viewjournal.cpp \
    utility.cpp \
    editissue.cpp

HEADERS  += mainwindow.h \
    editparsedreferences.h \
    viewparsedreferences.h \
    editrefindb.h \
    journal.h \
    addjournal.h \
    addvolume.h \
    addissue.h \
    parsewizard.h \
    addauthor.h \
    articles.h \
    editarticle.h \
    parsers.h \
    addparser.h \
    viewjournal.h \
    utility.h \
    editissue.h

FORMS    += mainwindow.ui \
    editparsedreferences.ui \
    viewparsedreferences.ui \
    editrefindb.ui \
    journal.ui \
    addjournal.ui \
    addvolume.ui \
    addissue.ui \
    parsewizard.ui \
    addauthor.ui \
    articles.ui \
    editarticle.ui \
    parsers.ui \
    addparser.ui \
    viewjournal.ui \
    editissue.ui

RESOURCES += \
    MyResources.qrc
