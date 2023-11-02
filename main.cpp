#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtSql>
#include <QDir>

#include "kategorimodel.h"
#include "booklistmodel.h"
#include "booklistdetailmodel.h"
#include "penerbitmodel.h"
#include "pengadaanbukumodel.h"
#include "editablepengadaanbukumodel.h"
#include "pengadaanmodel.h"

void initializeDatabase(QSqlDatabase &db) {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS Kategori("
                    "   kd_kategori VARCHAR(4) NOT NULL PRIMARY KEY,"
                    "   jenis VARCHAR(25) NOT NULL"
                    ")"))
        qFatal() << "Cannot create Kategori table " << query.lastError().text();
    if (!query.exec("CREATE TABLE IF NOT EXISTS Penerbit("
                    "   kd_penerbit VARCHAR (4) NOT NULL PRIMARY KEY,"
                    "   nama_penerbit VARCHAR(25) NOT NULL,"
                    "   alamat_penerbit VARCHAR(30) NOT NULL"
                    ")"))
         qFatal() << "Cannot create Penerbit table " << query.lastError().text();

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
                    "   jumlah_pengadaan_buku INT NOT NULL,"
                    "   PRIMARY KEY (kd_buku, kd_pengadaan),"
                    "   FOREIGN KEY (kd_buku)"
                    "       REFERENCES Buku(kd_buku),"
                    "   FOREIGN KEY (kd_pengadaan)"
                    "       REFERENCES Pengadaan(kd_pengadaan)"
                    ")"))
        qFatal() << "Cannot create Pengadaan_buku table " << query.lastError().text();
    if (!query.exec("CREATE TABLE IF NOT EXISTS Member("
                    "   kd_member VARCHAR (4) NOT NULL PRIMARY KEY,"
                    "   nama_member VARCHAR(25) NOT NULL,"
                    "   tgl_lahir VARCHAR(30) NOT NULL"
                    ")"))
        qFatal() << "Cannot create Member table " << query.lastError().text();
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BookListModel>("my.id.levirs.books", 1, 0, "BookListModel");
    qmlRegisterType<BookListDetailModel>("my.id.levirs.books", 1, 0, "BookListDetailModel");
    qmlRegisterType<KategoriModel>("my.id.levirs.books", 1, 0, "KategoriModel");
    qmlRegisterType<PenerbitModel>("Kelompok7.Perpus", 1, 0, "PenerbitModel");
    qmlRegisterType<PengadaanBukuModel>("Kelompok7.Perpus", 1, 0, "PengadaanBukuModel");
    qmlRegisterType<EditablePengadaanBukuModel>("Kelompok7.Perpus", 1, 0, "EditablePengadaanBukuModel");
    qmlRegisterType<PengadaanModel>("Kelompok7.Perpus", 1, 0, "PengadaanModel");

    QQuickStyle::setStyle("Material");

    QString dataDir = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first();
    QDir().mkdir(dataDir);

    QString dbPath = dataDir + "/data.db";

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

    engine.loadFromModule("qt-books-qml", "Main");

    return app.exec();
}
