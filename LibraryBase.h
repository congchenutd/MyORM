#ifndef LIBRARY_BASE_H
#define LIBRARY_BASE_H

#include <QMap>
#include <QString>

class Persistable;
class LibraryDAO;

/**
 * LibraryBase manages all the persistable objects
 * LibraryDAO loads and saves the library
 */
class LibraryBase
{
public:
    static LibraryBase* getInstance();

    // Add a persistable object to the library
    void addPersistable(Persistable* persistable);

    // Get a persistable with the given ID
    Persistable* getPersistable(const QString& className, int id);

    // Get all the objects of a given persistable class
    QList<Persistable*> getPersistables(const QString& className);

    // Load all the objects of registered in LibraryDAO
    void load();

    // Save all the objects of registered in LibraryDAO
    void save();

protected:
    LibraryBase();
    virtual ~LibraryBase() {}

protected:
    // Class name -> [ID -> Persistable]
    QMap<QString, QMap<int, Persistable*>> _name2Persistables;

    LibraryDAO* _dao;
};

#endif // LIBRARY_BASE_H
