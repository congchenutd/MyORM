#include "LibraryBase.h"
#include "LibraryDAO.h"
#include "Persistable.h"

LibraryBase* LibraryBase::getInstance()
{
    static LibraryBase instance;
    return &instance;
}

LibraryBase::LibraryBase()
    : _dao(LibraryDAO::getInstance())
{}

void LibraryBase::addPersistable(Persistable* persistable)
{
    QString className = persistable->metaObject()->className();
    _name2Persistables[className].insert(persistable->getID(), persistable);
}

Persistable* LibraryBase::getPersistable(const QString& className, int id) {
    return _name2Persistables[className][id];
}

QList<Persistable *> LibraryBase::getPersistables(const QString& className) {
    return _name2Persistables[className].values();
}

void LibraryBase::load() {
    _dao->load(this);
}

void LibraryBase::save() {
    _dao->save(this);
}

