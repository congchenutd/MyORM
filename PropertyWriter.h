#ifndef PROPERTYWRITER_H
#define PROPERTYWRITER_H

#include <QString>
#include <QVariant>

class Persistable;


/**
 * Converts a QVariant value (from sql table) into an object's property
 */
class PropertyLoader
{
public:
    virtual ~PropertyLoader();
    virtual bool        canLoad (const QVariant& value) const = 0;
    virtual QVariant    load    (const QVariant& value) const = 0;

    static QVariant loadValue(const QVariant& value);

private:
    static QList<PropertyLoader*> _loaders;
};

/**
 * Converts simple QVariant values
 */
class SimplePropertyLoader: public PropertyLoader
{
public:
    bool        canLoad (const QVariant& value) const;
    QVariant    load    (const QVariant& value) const;
};

/**
 * QList<QDate> is represented as QVariantList in Persistables,
 * and saved in SQL as a string separated by DATE_SEPARATOR, e.g., "2016-01-01##2016-01-02"
 *
 * This Loader converts that string into QVariantList, in which an item (QVariant) holds a QDate
 */
class DateListPropertyLoader: public PropertyLoader
{
public:
    bool        canLoad (const QVariant& value) const;
    QVariant    load    (const QVariant& value) const;
};

#endif // PROPERTYWRITER_H
