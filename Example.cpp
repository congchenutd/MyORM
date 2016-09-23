#include "Example.h"
#include "DAO.h"
#include <QDebug>

Invoice::Invoice(int id)
    : Persistable (id, InvoiceDAO::getInstance())
{
}

QDate Invoice::getDate() const {
    return _date;
}

void Invoice::setDate(const QDate& date) {
    _date = date;
}

double Invoice::getAmount() const {
    return _amount;
}

void Invoice::setAmount(double amount) {
    _amount = amount;
}

QString Invoice::getNote() const {
    return _note;
}

void Invoice::setNote(const QString& note) {
    _note = note;
}

Provider* Invoice::getProvider() const {
    return _provider;
}

void Invoice::setProvider(Provider* provider) {
    _provider = provider;
}

Provider::Provider(int id)
    : Persistable (id, ProviderDAO::getInstance())
{}

QString Provider::getName() const {
    return _name;
}

void Provider::setName(const QString& name) {
    _name = name;
}


ProviderDAO* ProviderDAO::getInstance()
{
    static ProviderDAO instance;
    return &instance;
}

ProviderDAO::ProviderDAO()
    : DAO("Provider")
{
    addMapping("Name", "NAME", "varchar");
    createTable();
}

Persistable* ProviderDAO::createObject(int id) {
    return new Provider(id);
}

InvoiceDAO* InvoiceDAO::getInstance()
{
    static InvoiceDAO instance;
    return &instance;
}

InvoiceDAO::InvoiceDAO()
    : DAO("Invoice")
{
    addMapping("Date",    "DATE",     "Date");
    addMapping("Amount",  "AMOUNT",   "double");
    addMapping("Note",    "NOTE",     "varchar");
    addRelationships(Relationship("Invoice", "Provider"));
    createTable();
}

Persistable* InvoiceDAO::createObject(int id) {
    return new Invoice(id);
}
