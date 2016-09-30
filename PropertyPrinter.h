#ifndef PROPERTYPRINTER_H
#define PROPERTYPRINTER_H

#include <QString>

class Persistable;
class QMetaProperty;

/**
 * PropertyPrinters convert the value (QVariant) of a QMetaProperty into QString
 * They are used to write properties into SQL db
 */
class PropertyPrinter
{
public:
    virtual ~PropertyPrinter();
    virtual QString print(Persistable* persistable, const QMetaProperty& property) const = 0;
};

class SimplePropertyPrinter: public PropertyPrinter
{
public:
    QString print(Persistable* persistable, const QMetaProperty& property) const;
};

class EnumPropertyPrinter: public PropertyPrinter
{
public:
    QString print(Persistable* persistable, const QMetaProperty& property) const;
};

class ListPropertyPrinter: public PropertyPrinter
{
public:
    QString print(Persistable* persistable, const QMetaProperty& property) const;
};


class PropertyPrinterFactory
{
public:
    PropertyPrinter* createPrinter(Persistable* persistable, const QMetaProperty& property) const;
};


/**
 * Prints the entire object
 */
class PersistablePrinter
{
public:
    QString print(Persistable* persistable) const;
};

#endif
