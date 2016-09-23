#include "Library.h"
#include "LibraryDAO.h"
#include "Persistable.h"

Library* Library::getInstance()
{
    static Library instance;
    return &instance;
}

Library::Library()
    : _dao(LibraryDAO::getInstance())
{}

void Library::addPersistable(Persistable* persistable)
{
    QString className = persistable->metaObject()->className();
    _name2Persistables[className].insert(persistable->getID(), persistable);
}

Persistable* Library::getPersistable(const QString& className, int id) {
    return _name2Persistables[className][id];
}

QList<Persistable *> Library::getPersistables(const QString& className) {
    return _name2Persistables[className].values();
}

void Library::load() {
    _dao->load(this);
}

void Library::save() {
    _dao->save(this);
}

