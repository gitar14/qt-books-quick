#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtSql>

#include "penerbitmodel.h"
#include "booklistmodel.h"
#include "booklistdetailmodel.h"
#include "booklisteditmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BookListModel>("my.id.levirs.books", 1, 0, "BookListModel");
    qmlRegisterType<BookListDetailModel>("my.id.levirs.books", 1, 0, "BookListDetailModel");
    qmlRegisterType<BookListEditModel>("my.id.levirs.books", 1, 0, "BookListEditModel");

    QQuickStyle::setStyle("Material");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("toko_buku");
    db.setUserName("root");
    db.setPassword("root");
    if (!db.open())
        qFatal() << "Cannot open database";

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    PenerbitModel model;
    engine.setInitialProperties({{ "penerbitModel", QVariant::fromValue(&model) }});
    engine.loadFromModule("qt-books-qml", "Main");

    return app.exec();
}
