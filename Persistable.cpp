#include "Persistable.h"
#include "DAO.h"

Persistable::Persistable(int id, DAO* dao)
    : _id(id), _dao(dao)
{}

int Persistable::getID() const {
    return _id;
}

DAO* Persistable::getDAO() const {
    return _dao;
}

void Persistable::destroy() {
    _dao->remove(this);
}

void Persistable::save() {
    _dao->save(this);
}
