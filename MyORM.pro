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
	LibraryBase.cpp \
    LibraryDAO.cpp \
    Example.cpp \
    PropertyPrinter.cpp \
    PropertyWriter.cpp

HEADERS  += \
    Persistable.h \
    DAO.h \
    Relationship.h \
	LibraryBase.h \
    LibraryDAO.h \
    Example.h \
    PropertyPrinter.h \
    PropertyWriter.h \
    Constants.h

FORMS    +=
