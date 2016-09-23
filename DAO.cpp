#include "DAO.h"
#include "Library.h"
#include "Persistable.h"
#include "LibraryDAO.h"
#include <QMetaProperty>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

DAO::DAO(const QString& className)
    : _className(className)
{}

/**
 * Save the given persistable into database
 */
void DAO::save(Persistable* persistable)
{
    if (exists(persistable))
        update(persistable);
    else
        insert(persistable);
}

/**
 * @return  whether the given persistale exists in the database
 */
bool DAO::exists(Persistable* persistable) const
{
    QSqlQuery query;
    query.exec(tr("select * from %1 where ID = %2")
               .arg(getTableName())
               .arg(persistable->getID()));
    return query.next();
}

/**
 * Remove the given persistable and its relations from the database
 */
void DAO::remove(Persistable* persistable)
{
    QSqlQuery query;
    query.exec(tr("delete from %1 where ID = %2")
               .arg(getTableName())
               .arg(persistable->getID()));

    removeRelationships(persistable);
}

void DAO::createTable()
{
    QStringList fields;
    fields << "ID int primary key";
    foreach (const Mapping& mapping, _mappings)
        fields << mapping._fieldName + " " + mapping._typeName;

    QSqlQuery query;
    query.exec(tr("create table %1 (%2)")
                    .arg(getTableName())
                    .arg(fields.join(",\n")));

    createRelationshipTables();
}

void DAO::createRelationshipTables()
{
    QSqlQuery query;
    foreach (const Relationship& relationship, getAllRelationships())
        query.exec(tr("create table %1 ( \
                      %2 int references %3 (ID) on delete cascade on update cascade, \
                      %4 int references %5 (ID) on delete cascade on update cascade, \
                      primary key (%2, %4) \
               )").arg(relationship.getRelationshipTableName())
                  .arg(relationship.getMainRelationID())
                  .arg(relationship.getMainTableName())
                  .arg(relationship.getForeignRelationID())
                  .arg(relationship.getForeignTableName())
                   );
}

void DAO::update(Persistable* persistable)
{
    QStringList sections;
    foreach (const Mapping& mapping, _mappings)
        sections << mapping._fieldName + " = :" + mapping._fieldName;

    QSqlQuery query;
    query.prepare(tr("update %1 set %2 where ID = %3")
                        .arg(getTableName())
                        .arg(sections.join(", "))
                        .arg(persistable->getID()));

    foreach (const Mapping& mapping, _mappings)
        query.bindValue(":" + mapping._fieldName, persistable->property(mapping._propertyName.toLatin1()));
    query.exec();

    updateRelationships(persistable);
}

void DAO::insert(Persistable* persistable)
{
    QStringList fields, values;
    fields << "ID";
    values << ":ID";
    foreach (const Mapping& mapping, _mappings)
    {
        fields << mapping._fieldName;
        values << ":" + mapping._fieldName;
    }

    QSqlQuery query;
    query.prepare(tr("insert into %1 (%2) values (%3)")
                        .arg(getTableName())
                        .arg(fields.join(", "))
                        .arg(values.join(", ")));

    query.bindValue(":ID", persistable->getID());
    foreach (const Mapping& mapping, _mappings)
        query.bindValue(":" + mapping._fieldName, persistable->property(mapping._propertyName.toLatin1()));
    query.exec();

    insertRelationships(persistable);
}

QString DAO::getTableName() const {
    return _className.toUpper();
}

QString DAO::getClassName() const {
    return _className;
}

int DAO::getNextID() const
{
    QSqlQuery query;
    query.exec(tr("select max(ID) from %1").arg(getTableName()));
    return query.next() ? query.value(0).toInt() + 1 : 1;
}

Persistable* DAO::load(int id)
{
    // Select the record from table
    QStringList fields;
    foreach (const Mapping& mapping, _mappings)
        fields << mapping._fieldName;

    QSqlQuery query;
    query.exec(tr("select %1 from %2 where id = %3")
               .arg(fields.join(", "))
               .arg(getTableName())
               .arg(id));
    if (query.next() == 0)
        return 0;

    // Instantiate the object
    Persistable* result = createObject(id);

    // Set values of the object properties
    foreach (const Mapping& mapping, _mappings)
    {
        QVariant value = query.value(mapping._fieldName);
        result->setProperty(mapping._propertyName.toLatin1(), value);
    }

    // Load relationships
    Library* library = Library::getInstance();
    foreach (const Relationship& relationship, getAllRelationships())
    {
        // Select foreign obj id from the relation table
        query.exec(tr("select %1 from %2 where %3 = %4")
                   .arg(relationship.getForeignRelationID())
                   .arg(relationship.getRelationshipTableName())
                   .arg(relationship.getMainRelationID())
                   .arg(id));

        if (query.next() != 0)
        {
            int foreignObjID = query.value(0).toInt();

            // Find the foreign object in the libary
            Persistable* foreignObj = library->getPersistable(relationship.getPropertyName(), foreignObjID);

            // Assign the foreign object to the peristable's property
            if (foreignObj != 0)
                result->setProperty(relationship.getPropertyName().toLatin1(),
                                    qVariantFromValue(foreignObj));
        }
    }

    return result;
}

/**
 * Update the relationships of a persistable
 */
void DAO::updateRelationships(Persistable* persistable)
{
    removeRelationships(persistable);
    insertRelationships(persistable);
}

void DAO::addRelationships(const Relationship& relationship) {
    _relationships << relationship;
}

QList<Relationship> DAO::getAllRelationships() const {
    return _relationships;
}

void DAO::removeRelationships(Persistable* persistable)
{
    QSqlQuery query;
    foreach (const Relationship& relationship, getAllRelationships())
        query.exec(tr("delete from %1 where %2 = %3)")
                    .arg(relationship.getRelationshipTableName())
                    .arg(relationship.getMainRelationID())
                    .arg(persistable->getID())
                   );
}

void DAO::insertRelationships(Persistable* persistable)
{
    QSqlQuery query;
    foreach (const Relationship& relationship, getAllRelationships())
    {
        const char* propertyName = relationship.getForeignClassName().toLatin1();
        Persistable* foreignObj = persistable->property(propertyName).value<Persistable*>();
        query.exec(tr("insert into %1 values (%2, %3)")
                                .arg(relationship.getRelationshipTableName())
                                .arg(persistable->getID())
                                .arg(foreignObj->getID()));
    }
}

void DAO::addMapping(const QString& propertyName, const QString& fieldName, const QString& typeName) {
    _mappings << Mapping(propertyName, fieldName, typeName);
}
