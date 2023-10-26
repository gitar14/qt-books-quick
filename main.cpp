#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtSql>
#include <QDir>
//#include <QFile>

#include "kategorimodel.h"
#include "booklistmodel.h"
#include "booklistdetailmodel.h"
#include "booklisteditmodel.h"

void initializeDatabase(QSqlDatabase &db) {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS Kategori("
                    "   kd_kategori VARCHAR(4) NOT NULL PRIMARY KEY,"
                    "   jenis VARCHAR(25) NOT NULL"
                    ")"))
        qFatal() << "Cannot create Kategori table " << query.lastError().text();

    if (!query.exec("CREATE TABLE IF NOT EXISTS Buku("
                    "   kd_buku VARCHAR(4) NOT NULL PRIMARY KEY,"
                    "   kd_kategori VARCHAR(4) NOT NULL,"
                    "   judul VARHCHAR(25) NOT NULL,"
                    "   jumlah_buku INTEGER NOT NULL,"
                    "   penulis VARCHAR(25) NOT NULL,"
                    "   tahun_terbit INTEGER NOT NULL,"
                    "   FOREIGN KEY (kd_kategori)"
                    "       REFERENCES Kategori(kd_kategori)"
                    ")"))
        qFatal() << "Cannot create Buku table " << query.lastError().text();

    if (!query.exec("CREATE TABLE IF NOT EXISTS Pengadaan("
                    "   kd_pengadaan VARCHAR(4) NOT NULL PRIMARY KEY,"
                    "   sumber VARCHAR(25) NOT NULL"
                    ")"))
        qFatal() << "Cannot create Pengadaan table " << query.lastError().text();

    if (!query.exec("CREATE TABLE IF NOT EXISTS Pengadaan_buku("
                    "   kd_buku VARCHAR(4) NOT NULL,"
                    "   kd_pengadaan VARCHAR(4) NOT NULL,"
                    "   PRIMARY KEY (kd_buku, kd_pengadaan),"
                    "   FOREIGN KEY (kd_buku)"
                    "       REFERENCES Buku(kd_buku),"
                    "   FOREIGN KEY (kd_pengadaan)"
                    "       REFERENCES Pengadaan(kd_pengadaan)"
                    ")"))
        qFatal() << "Cannot create Pengadaan_buku table " << query.lastError().text();
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BookListModel>("my.id.levirs.books", 1, 0, "BookListModel");
    qmlRegisterType<BookListDetailModel>("my.id.levirs.books", 1, 0, "BookListDetailModel");
    qmlRegisterType<BookListEditModel>("my.id.levirs.books", 1, 0, "BookListEditModel");
    qmlRegisterType<KategoriModel>("my.id.levirs.books", 1, 0, "KategoriModel");

    QQuickStyle::setStyle("Material");

    QString dataDir = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first();
    QDir().mkdir(dataDir);

    QString dbPath = dataDir + "/data.db";
//    QFile dbFile(dbPath);
//    if (!dbFile.exists()) {
//        dbFile.open(QFile::WriteOnly);
//        dbFile.close();
//    }


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    qInfo() << db.databaseName();

    if (!db.open())
        qFatal() << "Cannot open database";

    initializeDatabase(db);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    KategoriModel model;
    engine.loadFromModule("qt-books-qml", "Main");

    return app.exec();
}
