#include "Relationship.h"

Relationship::Relationship(const QString& mainClassName,
                           const QString& foreignClassName)
    : _mainClassName   (mainClassName),
      _foreignClassName(foreignClassName)
{}

QString Relationship::getMainClassName() const {
    return _mainClassName;
}

QString Relationship::getForeignClassName() const {
    return _foreignClassName;
}

QString Relationship::getMainTableName() const {
    return getMainClassName().toUpper();
}

QString Relationship::getForeignTableName() const {
    return getForeignClassName().toUpper();
}

QString Relationship::getMainID() const {
    return getMainTableName() + ".ID";
}

QString Relationship::getForeignID() const {
    return getForeignTableName() + ".ID";
}

QString Relationship::getMainRelationID() const {
    return getMainTableName() + "ID";
}

QString Relationship::getForeignRelationID() const {
    return getForeignTableName() + "ID";
}

QString Relationship::getRelationshipTableName() const {
    return getMainTableName() + "_" + getForeignTableName();
}

QString Relationship::getPropertyName() const {
    return getForeignClassName();
}
