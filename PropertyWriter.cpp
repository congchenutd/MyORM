#include "Persistable.h"
#include "PropertyWriter.h"
#include "PropertyPrinter.h"
#include "Constants.h"
#include <QDate>

PropertyLoader::~PropertyLoader() {}

QList<PropertyLoader*> PropertyLoader::_loaders;

/**
 * Converts the value into a value compatible with QObject's property system
 */
QVariant PropertyLoader::loadValue(const QVariant& value)
{
    _loaders << new DateListPropertyLoader
             << new SimplePropertyLoader;

    foreach (PropertyLoader* loader, _loaders)
        if (loader->canLoad(value))
            return loader->load(value);

    return QVariant();
}

///////////////////////////////////////////////////////////////////////////////////
bool SimplePropertyLoader::canLoad(const QVariant &value) const
{
    Q_UNUSED(value)
    return true;
}

QVariant SimplePropertyLoader::load(const QVariant& value) const {
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////

/**
 * Determine if the QVariant value is a string separated by DATE_SEPARATOR,
 * e.g., "2016-01-01##2016-01-02"
 */
bool DateListPropertyLoader::canLoad(const QVariant& value) const
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

QVariant DateListPropertyLoader::load(const QVariant& value) const
{
    QString stringValue = value.toString();
    QStringList sections = stringValue.split(LIST_SEPARATOR);
    QVariantList list;
    foreach (const QString& section, sections)
        list << QDate::fromString(section, DATE_FORMAT);

    return list;
}
