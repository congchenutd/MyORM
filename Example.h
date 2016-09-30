#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "DAO.h"
#include "Persistable.h"

#include <QDate>
#include <QVariantList>

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
public:
    enum State {Unfiled, Filed, Paid, Deposited};
    Q_ENUMS(State)

    Q_OBJECT

    Q_PROPERTY(QVariantList ServiceDates    READ getServiceDates    WRITE setServiceDates)
    Q_PROPERTY(QDate        InvoiceDate     READ getInvoiceDate     WRITE setInvoiceDate)
    Q_PROPERTY(double       Amount          READ getAmount          WRITE setAmount)
    Q_PROPERTY(QString      Note            READ getNote            WRITE setNote)
    Q_PROPERTY(State        State           READ getState           WRITE setState)
    Q_PROPERTY(Provider*    Provider        READ getProvider        WRITE setProvider)

public:
    Invoice(int id);

    QVariantList getServiceDates() const;
    void setServiceDates(const QVariantList& dates);

    QDate getInvoiceDate() const;
    void setInvoiceDate(const QDate& date);

    double getAmount() const;
    void setAmount(double amount);

    QString getNote() const;
    void setNote(const QString& note);

    State getState() const;
    void setState(State state);

    Provider* getProvider() const;
    void setProvider(Provider* provider);

private:
    QVariantList    _serviceDates;
    QDate           _invoiceDate;
    double          _amount;
    QString         _note;
    State           _state;
    Provider*       _provider;
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
