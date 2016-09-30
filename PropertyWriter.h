#ifndef PROPERTYWRITER_H
#define PROPERTYWRITER_H

#include <QString>
#include <QVariant>


class Persistable;


/**
 * Writers write a QVariant value (from sql table) into an object's property
 */
class PropertyWriter
{
public:
    virtual ~PropertyWriter();
    virtual bool canWrite(const QVariant& value) const;
    virtual void write(Persistable* persistable, const QString& propertyName, const QVariant& value) const;
};

/**
 * QList<QDate> is represented as QVariantList in Persistables,
 * and saved in SQL as a string separated by DATE_SEPARATOR, e.g., "2016-01-01##2016-01-02"
 *
 * This writer converts that string into QVariantList, in which an item (QVariant) holds a QDate
 */
class DateListPropertyWriter: public PropertyWriter
{
public:
    bool canWrite(const QVariant& value) const;
    void write(Persistable* persistable, const QString& propertyName, const QVariant& value) const;
};

/**
 * Creates a writer base on the value
 */
class PropertyWriterFactory
{
public:
    static PropertyWriterFactory* getInstance();
    PropertyWriter* createWriter(const QVariant& value) const;

private:
    PropertyWriterFactory();

private:
    QList<PropertyWriter*> _writers;
};

#endif // PROPERTYWRITER_H
