#include "DAO.h"
#include "Library.h"
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

void LibraryDAO::load(Library* library)
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

void LibraryDAO::save(Library* library)
{
    if (QSqlDatabase::database().transaction())
    {
        foreach (DAO* dao, _daos) {
            foreach (Persistable* persistable, library->getPersistables(dao->getClassName()))
                persistable->save();
        }
        QSqlDatabase::database().commit();
    }
}

LibraryDAO::LibraryDAO() {}
