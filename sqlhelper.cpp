#include "sqlhelper.h"
#include <QList>
#include <QHash>
#include <QVariant>
#include <QSqlError>

namespace SQLHelper {
    QString generateArrayBinds(QString prefix, const QStringList& list, QHash<QString, QVariant> &binds)
    {
        QStringList bindResults;
        for (qsizetype i = 0; i < list.length(); i++) {
            QString name = prefix + QString::number(i);
            bindResults.push_back(name);
            binds[name] = list.at(i);
        }

        return bindResults.join(",");
    }

    void applyBindMaps(QSqlQuery &query, const QHash<QString, QVariant> &binds)
    {
        for (QHash<QString, QVariant>::const_iterator it = binds.begin(); it != binds.end(); it++) {
            query.bindValue(it.key(), it.value());
        }
    }

    void initializeDatabase(QSqlDatabase &db)
    {

        QSqlQuery query(db);
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
                        "   kd_penerbit VARCHAR(4) NOT NULL,"
                        "   judul VARCHAR(25) NOT NULL,"
                        "   jumlah_buku INTEGER NOT NULL,"
                        "   penulis VARCHAR(25) NOT NULL,"
                        "   tahun_terbit INTEGER NOT NULL,"
                        "   FOREIGN KEY (kd_kategori)"
                        "       REFERENCES Kategori(kd_kategori), "
                        "   FOREIGN KEY (kd_penerbit)"
                        "       REFERENCES Penerbit(kd_penerbit)"
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
                        "   nama_depan_member VARCHAR(25) NOT NULL,"
                        "   nama_belakang_member VARCHAR(25) NOT NULL,"
                        "   tanggal_lahir DATE NOT NULL"
                        ")"))
            qFatal() << "Cannot create Member table " << query.lastError().text();
        if (!query.exec("CREATE TABLE IF NOT EXISTS Peminjaman("
                        "   kd_peminjaman VARCHAR(4) NOT NULL PRIMARY KEY,"
                        "   kd_member VARCHAR(4) NOT NULL,"
                        "   tanggal_peminjaman DATE NOT NULL,"
                        "   lama_peminjaman INTEGER NOT NULL,"
                        "   FOREIGN KEY (kd_member)"
                        "       REFERENCES Member(kd_member)"
                        ")"))
            qFatal() << "Cannot create Peminjaman table " << query.lastError().text();

        if (!query.exec("CREATE TABLE IF NOT EXISTS Peminjaman_buku("
                        "   kd_buku VARCHAR(4) NOT NULL,"
                        "   kd_peminjaman VARCHAR(4) NOT NULL,"
                        "   PRIMARY KEY (kd_buku, kd_peminjaman),"
                        "   FOREIGN KEY (kd_buku)"
                        "       REFERENCES Buku(kd_buku),"
                        "   FOREIGN KEY (kd_peminjaman)"
                        "       REFERENCES Peminjaman(kd_peminjaman)"
                        ")"))
            qFatal() << "Cannot create Peminjaman_buku table " << query.lastError().text();

    }

    void clearDatabase(QSqlDatabase &db)
    {
        QStringList tableList{
            "Peminjaman_buku",
            "Peminjaman",
            "Member",
            "Pengadaan_buku",
            "Pengadaan",
            "Buku",
            "Penerbit",
            "Kategori"
        };

        QSqlQuery query;
        for (QStringList::iterator it = tableList.begin(); it != tableList.end(); it++) {
            query.prepare(QStringLiteral("DROP TABLE IF EXISTS %1").arg(*it));
            if (!query.exec()) {
                qFatal() << "Cannot drop table " << *it << " " << query.lastError().text();
            }
        }
    }

}
