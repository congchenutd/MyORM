#include "Example.h"
#include <QApplication>
#include <QSqlQuery>
#include <QDebug>
#include "DAO.h"
#include "LibraryBase.h"
#include "LibraryDAO.h"

bool openDB(const QString& name)
{
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName(name);
	if(!database.open())
		return false;

	QSqlQuery query;
	query.exec("PRAGMA foreign_keys = ON");
	return true;
}

int main(int argc, char *argv[])
{
	openDB("Test.db");
	LibraryBase* library = LibraryBase::getInstance();

	Provider* provider = new Provider(2);
	provider->setName("Hello");
	library->addPersistable(provider);

	Invoice* invoice = new Invoice(1);
	invoice->setAmount(100);
	invoice->setDate(QDate::fromString("2016-01-01", "yyyy-MM-dd"));
	invoice->setNote("asdf");
	invoice->setProvider(provider);
	library->addPersistable(invoice);

	LibraryDAO* libraryDAO = LibraryDAO::getInstance();
	libraryDAO->registerDAO(ProviderDAO::getInstance());
	libraryDAO->registerDAO(InvoiceDAO::getInstance());

	libraryDAO->save(library);

	provider = (Provider*) ProviderDAO::getInstance()->load(2);
	invoice  = (Invoice*)  InvoiceDAO ::getInstance()->load(1);

	qDebug() << provider->getID() << invoice->getID();
}
