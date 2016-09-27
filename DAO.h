#ifndef DAO_H
#define DAO_H

#include "Relationship.h"

#include <QObject>

class Persistable;

/**
 * A mapping from class property to SQL field
 */
struct Mapping
{
    Mapping(const QString& propertyName, const QString& fieldName, const QString& typeName)
        : _propertyName(propertyName),
          _fieldName(fieldName),
          _typeName(typeName) {}

    QString _propertyName;
    QString _fieldName;
    QString _typeName;
};

/**
 * DAO is the base for all DAO classes
 * Each DAO takes care of one Persistable
 */
class DAO: public QObject
{
public:
    DAO(const QString& className);
    virtual ~DAO() {}

    // Save the persistable object into the database
    void save(Persistable* persistable);

    // Whether the persistable exists in the database
    bool exists(Persistable* persistable) const;

    // SQL table name of the persistables
    QString getTableName() const;

    // Persistable class name, same as table name
    QString getClassName() const;

    // Generate next ID for the persistable, starting from 1
    int getNextID() const;

    // Load the persistable with the given id
    Persistable* load(int id);

    // delete the persistable and its relations
    void remove(Persistable* persistable);

    // Add a property->field mapping
    void addMapping(const QString& propertyName, const QString& fieldName, const QString& typeName);

    // Add an entity relationship
    void addRelationships(const Relationship& relationship);

    QList<Relationship> getAllRelationships() const;

    // Create the SQL table for the persistable class
    void createTable();

protected:
    // Create SQL table for the relationships of the persistable
    void createRelationshipTables();

    // update an existing persistable in the db
    void update(Persistable* persistable);

    // insert a new persistable into db
    void insert(Persistable* persistable);

    // update relations of a persistable
    void updateRelationships(Persistable* persistable);

    // remove all relations of a persistable
    void removeRelationships(Persistable* persistable);

    // insert relations of a persistable into db
    void insertRelationships(Persistable* persistable);

    // Create an instance of the persistable class
    // Subclasses have to override this method to create a concrete Persistable object
    virtual Persistable* createObject(int id) = 0;

protected:
    // Class name of the persistable
    QString _className;

    QList<Relationship> _relationships;

    // Property mappings
    QList<Mapping>  _mappings;
};


#endif // DAO_H
