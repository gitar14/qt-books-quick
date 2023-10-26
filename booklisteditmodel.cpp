#include "booklisteditmodel.h"

#include <QtSql>

BookListEditModel::BookListEditModel(QObject *parent)
    : QObject{parent}
{
    
}

QString BookListEditModel::kode()
{
    return mKode;
}

void BookListEditModel::setKodeId(QString Id)
{
    mKode = Id;
    emit kodeChanged();

    QSqlQuery query;

    QString judul = "";
    QString penulis = "";
    int jumlahBuku = 0;
    int tahunTerbit = 0;
    mKodeKategori = "";

    if (mKode.length() != 0) {
        query.prepare("SELECT * FROM Buku WHERE kd_buku = :kode");
        query.bindValue(":kode", mKode);

        if (!query.exec())
            qFatal() << query.lastError().text();

        if (query.next()) {
            QSqlRecord record = query.record();
            judul = record.value("judul").toString();
            penulis = record.value("penulis").toString();
            jumlahBuku = record.value("jumlah_buku").toInt();
            tahunTerbit = record.value("tahun_terbit").toInt();
            mKodeKategori = record.value("kd_kategori").toString();
        }
    }

    setJudul(judul);
    setPenulis(penulis);
    setJumlahBuku(jumlahBuku);
    setTahunTerbit(tahunTerbit);

    mKategoriList.clear();

    query.prepare("SELECT kd_kategori, jenis FROM Kategori");

    if (!query.exec())
        qFatal() << query.lastError().text();

    while (query.next()) {
        QSqlRecord record = query.record();

        mKategoriList[record.value(0).toString()] = record.value(1).toString();
    }

    emit kategoriListChanged();

    int kategoriIndex = -1;

    if (mKodeKategori.length() != 0) {
        QStringList kodeList = mKategoriList.keys();
        for (int i = 0; i < kodeList.length(); i++) {
            if (kodeList[i] == mKodeKategori) {
                kategoriIndex = i;
                break;
            }
        }
    }

    setKategoriIndex(kategoriIndex);
}

void BookListEditModel::setIsNew()
{
    setKodeId("");
}

QString BookListEditModel::judul()
{
    return mJudul;
}

QString BookListEditModel::penulis()
{
    return mPenulis;
}

int BookListEditModel::jumlahBuku()
{
    return mJumlahBuku;
}

int BookListEditModel::kategoriIndex()
{
    return mKategoriIndex;
}

QStringList BookListEditModel::kategoriList()
{
    return mKategoriList.values();
}

void BookListEditModel::setJudul(QString judul)
{
    if (mJudul == judul) return;
    mJudul = judul;
    emit judulChanged();
}

void BookListEditModel::setPenulis(QString penulis)
{
    if (mPenulis == penulis) return;
    mPenulis = penulis;
    emit penulisChanged();
}

void BookListEditModel::setJumlahBuku(int jumlah)
{
    if (mJumlahBuku == jumlah) return;
    mJumlahBuku = jumlah;
    emit jumlahBukuChanged();
}

void BookListEditModel::setKategoriIndex(int index)
{
    if (mKategoriIndex == index) return;
    mKategoriIndex = index;
    emit kategoriIndexChanged();

    mKodeKategori = mKategoriList.keys().value(index);
    qInfo() << mKodeKategori;
}

void BookListEditModel::submit()
{
    QSqlQuery query;
    if (mKode.length() == 0) {
        QSqlQuery idQuery;
        if (!idQuery.exec("SELECT MAX(CAST(kd_buku AS UNSIGNED)) FROM Buku"))
            qFatal() << "Error get max id " << idQuery.lastError();

        int maxId = -1;
        if (idQuery.next()) {
            maxId = idQuery.value(0).toInt();
        }

        query.prepare("INSERT INTO Buku("
                      " kd_buku,"
                      " judul,"
                      " penulis,"
                      " jumlah_buku,"
                      " tahun_terbit"
                      " kd_kategori,"
                      ") VALUES ("
                      " :kode,"
                      " :judul,"
                      " :penulis,"
                      " :jumlah,"
                      " :tahun_terbit,"
                      " :kategori,"
                      " 0"
                      ")");
        query.bindValue(":kode", QString::number(maxId + 1).rightJustified(4, '0'));
    } else {
        query.prepare("UPDATE Buku SET "
                      "judul = :judul,"
                      "penulis = :penulis,"
                      "jumlah_buku = :jumlah,"
                      "tahun_terbit = :tahun_terbit,"
                      "kd_kategori = :kategori "
                      "WHERE kd_buku = :kode");
        query.bindValue(":kode", mKode);
    }

    query.bindValue(":judul", mJudul);
    query.bindValue(":penulis", mPenulis);
    query.bindValue(":jumlah", mJumlahBuku);
    query.bindValue(":tahun_terbit", mTahunTerbit);
    query.bindValue(":kategori", mKodeKategori);

    if (!query.exec())
        qFatal() << "Error submit " << query.lastError().text();


}

int BookListEditModel::tahunTerbit() const
{
    return mTahunTerbit;
}

void BookListEditModel::setTahunTerbit(int newTahunTerbit)
{
    if (mTahunTerbit == newTahunTerbit)
        return;
    mTahunTerbit = newTahunTerbit;
    emit tahunTerbitChanged();
}
