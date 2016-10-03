#include "Persistable.h"
#include "PropertyWriter.h"
#include "PropertyPrinter.h"
#include "Constants.h"
#include <QDate>

PropertyWriter::~PropertyWriter() {}

bool PropertyWriter::canWrite(const QVariant& value) const
{
    Q_UNUSED(value)
    return true;
}

void PropertyWriter::write(Persistable* persistable, const QString& propertyName, const QVariant& value) const
{
    persistable->setProperty(propertyName.toLatin1(), value);
}

////////////////////////////////////////////////////////////////////////////////////////

/**
 * Determine if the QVariant value is a string separated by DATE_SEPARATOR,
 * e.g., "2016-01-01##2016-01-02"
 */
bool DateListPropertyWriter::canWrite(const QVariant& value) const
{
    if (value.canConvert(QVariant::String))
    {
        QString stringValue = value.toString();
        if (stringValue.contains(LIST_SEPARATOR))
        {
            QStringList sections = stringValue.split(LIST_SEPARATOR);
            foreach (const QString& section, sections)
                if (!QDate::fromString(section, DATE_FORMAT).isValid())
                    return false;
            return true;
        }
    }
    return false;
}

void DateListPropertyWriter::write(Persistable* persistable, const QString& propertyName, const QVariant& value) const
{
    QString stringValue = value.toString();
    QStringList sections = stringValue.split(LIST_SEPARATOR);
    QVariantList list;
    foreach (const QString& section, sections)
        list << QDate::fromString(section, DATE_FORMAT);

    persistable->setProperty(propertyName.toLatin1(), list);
}

////////////////////////////////////////////////////////////////////////////////////////////
PropertyWriterFactory::PropertyWriterFactory() {
    _writers << new DateListPropertyWriter
             << new PropertyWriter;
}

PropertyWriterFactory* PropertyWriterFactory::getInstance()
{
    static PropertyWriterFactory instance;
    return &instance;
}

PropertyWriter* PropertyWriterFactory::createWriter(const QVariant& value) const
{
    foreach (PropertyWriter* writer, _writers)
        if (writer->canWrite(value))
            return writer;
    return 0;
}

