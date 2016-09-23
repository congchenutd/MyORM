#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "DAO.h"
#include "Persistable.h"

#include <QDate>

class Provider: public Persistable
{
    Q_OBJECT

    Q_PROPERTY(QString Name READ getName WRITE setName)

public:
    Provider(int id);

    QString getName() const;
    void setName(const QString& name);

private:
    QString _name;
};

class Invoice: public Persistable
{
    Q_OBJECT

    Q_PROPERTY(QDate        Date        READ getDate        WRITE setDate)
    Q_PROPERTY(double       Amount      READ getAmount      WRITE setAmount)
    Q_PROPERTY(QString      Note        READ getNote        WRITE setNote)
    Q_PROPERTY(Provider*    Provider    READ getProvider    WRITE setProvider)

public:
    Invoice(int id);

    QDate getDate() const;
    void setDate(const QDate& date);

    double getAmount() const;
    void setAmount(double amount);

    QString getNote() const;
    void setNote(const QString& note);

    Provider* getProvider() const;
    void setProvider(Provider* provider);

private:
    QDate       _date;
    double      _amount;
    QString     _note;
    Provider*   _provider;
};

class ProviderDAO: public DAO
{
public:
    static ProviderDAO* getInstance();

private:
    ProviderDAO();

protected:
    Persistable* createObject(int id);
};

class InvoiceDAO: public DAO
{
public:
    static InvoiceDAO* getInstance();

private:
    InvoiceDAO();

protected:
    Persistable* createObject(int id);
};

#endif // EXAMPLE_H
