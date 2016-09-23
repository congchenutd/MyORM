#-------------------------------------------------
#
# Project created by QtCreator 2016-09-21T15:03:59
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyORM
TEMPLATE = app


SOURCES +=\
    Main.cpp \
    Persistable.cpp \
    DAO.cpp \
    Relationship.cpp \
    Library.cpp \
    LibraryDAO.cpp \
    Example.cpp

HEADERS  += \
    Persistable.h \
    DAO.h \
    Relationship.h \
    Library.h \
    LibraryDAO.h \
    Example.h

FORMS    +=
