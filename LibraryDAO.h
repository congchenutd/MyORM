#ifndef LIBRARYDAO_H
#define LIBRARYDAO_H

#include <QList>
#include <QObject>

class LibraryBase;
class DAO;

/**
 * LibraryDAO loads/saves persistable objects between Library and DB
 */
class LibraryDAO: public QObject
{
public:
    static LibraryDAO* getInstance();

    // A persistable class is registered via its DAO object
    void registerDAO(DAO* dao);

    void load(LibraryBase* library);
    void save(LibraryBase* library);

private:
    LibraryDAO();

private:
    QList<DAO*> _daos;
};

#endif // LIBRARYDAO_H
