#ifndef RELATIONSHIPDAO_H
#define RELATIONSHIPDAO_H

#include <QString>

/**
 * A relationship between 2 SQL tables
 */
class Relationship
{
public:
    Relationship(const QString& mainClassName, const QString& foreignClassName);

    QString getMainClassName()          const;
    QString getForeignClassName()       const;
    QString getMainTableName()          const;
    QString getForeignTableName()       const;
    QString getMainID()                 const;  // ID in the main table
    QString getForeignID()              const;  // ID in the foreign table
    QString getMainRelationID()         const;  // Main object ID in the relation table
    QString getForeignRelationID()      const;  // Foreign object ID in the relation table
    QString getRelationshipTableName()  const;
    QString getPropertyName()           const;  // Foreign property name in the main class

private:
    QString _mainClassName;
    QString _foreignClassName;
};

#endif // RELATIONSHIPDAO_H
