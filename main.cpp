#include "Example.h"
#include <QApplication>
#include <QSqlQuery>
#include <QDebug>
#include "DAO.h"
#include "LibraryBase.h"
#include "LibraryDAO.h"
#include "PropertyPrinter.h"
#include "Constants.h"

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
	LibraryDAO* libraryDAO = LibraryDAO::getInstance();
	libraryDAO->registerDAO(ProviderDAO::getInstance());
	libraryDAO->registerDAO(InvoiceDAO::getInstance());
	LibraryBase* library = LibraryBase::getInstance();

//	Provider* provider = new Provider(2);
//	provider->setName("Hello");
//	library->addPersistable(provider);

	Invoice* invoice = new Invoice(1);
	invoice->setAmount(100);
	invoice->setServiceDates(QVariantList()
							 << QDate::fromString("2016-01-01", DATE_FORMAT)
							 << QDate::fromString("2016-01-02", DATE_FORMAT));
	invoice->setInvoiceDate(QDate::fromString("2016-01-03", DATE_FORMAT));
	invoice->setNote("asdf");
	invoice->setState(Invoice::Deposited);
//	invoice->setProvider(provider);
	library->addPersistable(invoice);

	PersistablePrinter printer;
	qDebug() << printer.toText(invoice);

	libraryDAO->save(library);

//	provider = (Provider*) ProviderDAO::getInstance()->load(2);
	invoice  = (Invoice*)  InvoiceDAO ::getInstance()->load(1);

	qDebug() << printer.toText(invoice)
			 << printer.toHtml(invoice);
}
