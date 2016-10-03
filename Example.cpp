#include "Example.h"
#include "DAO.h"
#include <QDebug>

Invoice::Invoice(int id)
    : Persistable (id, InvoiceDAO::getInstance()),
      _provider(0)
{
}

QVariantList Invoice::getServiceDates() const {
    return _serviceDates;
}

void Invoice::setServiceDates(const QVariantList& dates) {
    _serviceDates = dates;
}

QDate Invoice::getInvoiceDate() const {
    return _invoiceDate;
}

void Invoice::setInvoiceDate(const QDate& date) {
    _invoiceDate = date;
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

Invoice::State Invoice::getState() const {
    return _state;
}

void Invoice::setState(Invoice::State state) {
    _state = state;
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
    addMapping("ServiceDates",  "SERVICEDATES", "varchar");
    addMapping("InvoiceDate",   "INVOICEDATE",  "Date");
    addMapping("Amount",        "AMOUNT",       "double");
    addMapping("Note",          "NOTE",         "varchar");
    addMapping("State",         "STATE",        "varchar");
    addRelationships(Relationship("Invoice", "Provider"));
    createTable();
}

Persistable* InvoiceDAO::createObject(int id) {
    return new Invoice(id);
}
