#include "Persistable.h"
#include "PropertyPrinter.h"
#include "Constants.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaEnum>

PropertyPrinter::~PropertyPrinter() {}

QString SimplePropertyPrinter::print(Persistable* persistable, const QMetaProperty& property) const {
    return persistable->property(property.name()).toString();
}


QString EnumPropertyPrinter::print(Persistable* persistable, const QMetaProperty& property) const
{
    int value = persistable->property(property.name()).toInt(); // the value of an enum is saved as int in QVariant
    return property.enumerator().valueToKeys(value);
}


QString ListPropertyPrinter::print(Persistable* persistable, const QMetaProperty& property) const
{
    QStringList result;
    foreach (const QVariant& value, persistable->property(property.name()).toList())
        result << value.toString();

    return result.join(LIST_SEPARATOR);
}


PropertyPrinter* PropertyPrinterFactory::createPrinter(Persistable* persistable, const QMetaProperty& property) const
{
    if (property.isEnumType())
        return new EnumPropertyPrinter;

    QVariant value = persistable->property(property.name());
    if (value.type() == QVariant::List)
        return new ListPropertyPrinter;

    return new SimplePropertyPrinter;
}

QString PersistablePrinter::print(Persistable* persistable) const
{
    QStringList result;

    PropertyPrinterFactory factory;
    const QMetaObject* metaObj = persistable->metaObject();
    const int count = metaObj->propertyCount();
    for (int i = metaObj->propertyOffset(); i < count; ++i)
    {
        QMetaProperty property = metaObj->property(i);
        PropertyPrinter* printer = factory.createPrinter(persistable, property);
        result << QString::fromLatin1(property.name()) + ": " + printer->print(persistable, property);
    }
    return result.join("\n");
}

