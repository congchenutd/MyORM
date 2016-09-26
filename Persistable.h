#ifndef PERSISTABLE_H
#define PERSISTABLE_H

#include <QObject>

class DAO;

/**
 * Anything that needs to be persisted in the database
 * Each Persistable has a shared concrete DAO object for loading and saving it
 * Each Persistable has an ID, and its corresponding table has a ID field
 */
class Persistable: public QObject
{
    Q_OBJECT

public:
    Persistable(int id, DAO* dao);
    virtual ~Persistable() {}

    int  getID()  const;
    DAO* getDAO() const;

    // Remove this object from the database
    // WARNING: stop using this object after destroy()
    virtual void destroy();

    // Write the object into database
    virtual void save();

protected:
    int     _id;
    DAO*    _dao;
};

#endif // PERSISTABLE_H
