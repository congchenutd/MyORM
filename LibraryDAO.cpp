#include "DAO.h"
#include "LibraryBase.h"
#include "LibraryDAO.h"
#include "Persistable.h"

#include <QSqlQuery>
#include <QVariant>

LibraryDAO* LibraryDAO::getInstance()
{
    static LibraryDAO instance;
    return &instance;
}

void LibraryDAO::registerDAO(DAO* dao) {
    _daos << dao;
}

void LibraryDAO::load(LibraryBase* library)
{
    QSqlQuery query;
    foreach (DAO* dao, _daos)
    {
        // Get all the ID in the table
        query.exec(tr("select ID from %1 Order By ID").arg(dao->getTableName()));
        while (query.next() != 0)
        {
            // Use this DAO to load the object with the ID into library
            Persistable* persistable = dao->load(query.value(0).toInt());
            library->addPersistable(persistable);
        }
    }
}

void LibraryDAO::save(LibraryBase* library)
{
    if (QSqlDatabase::database().transaction())
    {
        foreach (DAO* dao, _daos) {
            QList<Persistable*> persistables = library->getPersistables(dao->getClassName());
            foreach (Persistable* persistable, persistables)
                persistable->save();
        }
        QSqlDatabase::database().commit();
    }
}

LibraryDAO::LibraryDAO() {}
