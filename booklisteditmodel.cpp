#include "booklisteditmodel.h"

#include <QtSql>

BookListEditModel::BookListEditModel(QObject *parent)
    : QObject{parent}
{
    
}

QString BookListEditModel::bookId()
{
    return mBookId;
}

void BookListEditModel::setBookId(QString Id)
{
    mBookId = Id;
    emit bookIdChanged();

    QSqlQuery query;

    QString judul = "";
    QString penulis = "";
    int jumlahBuku = 0;
    mPenerbitKode = "";

    if (mBookId.length() != 0) {
        query.prepare("SELECT * FROM Buku WHERE Kode_buku = :kode");
        query.bindValue(":kode", mBookId);

        if (!query.exec())
            qFatal() << query.lastError().text();

        if (query.next()) {
            QSqlRecord record = query.record();
            judul = record.value("Judul").toString();
            penulis = record.value("Pengarang").toString();
            jumlahBuku = record.value("Jml_buku").toInt();
            mPenerbitKode = record.value("Kode_penerbit").toString();
        }
    }

    setJudul(judul);
    setPenulis(penulis);
    setJumlahBuku(jumlahBuku);

    mPenerbitList.clear();

    query.prepare("SELECT Kode_penerbit, Nm_penerbit FROM Penerbit");

    if (!query.exec())
        qFatal() << query.lastError().text();

    while (query.next()) {
        QSqlRecord record = query.record();

        mPenerbitList[record.value(0).toString()] = record.value(1).toString();
    }

    emit penerbitListChanged();

    int penerbitIndex = -1;

    if (mPenerbitKode.length() != 0) {
        QStringList kodeList = mPenerbitList.keys();
        for (int i = 0; i < kodeList.length(); i++) {
            if (kodeList[i] == mPenerbitKode) {
                penerbitIndex = i;
                break;
            }
        }
    }

    setPenerbitIndex(penerbitIndex);
}

void BookListEditModel::setIsNew()
{
    setBookId("");
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

int BookListEditModel::penerbitIndex()
{
    return mPenerbitIndex;
}

QStringList BookListEditModel::penerbitList()
{
    return mPenerbitList.values();
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

void BookListEditModel::setPenerbitIndex(int index)
{
    if (mPenerbitIndex == index) return;
    mPenerbitIndex = index;
    emit penerbitIndexChanged();

    mPenerbitKode = mPenerbitList.keys().value(index);
    qInfo() << mPenerbitKode;
}

void BookListEditModel::submit()
{
    QSqlQuery query;
    if (mBookId.length() == 0) {
        QSqlQuery idQuery;
        if (!idQuery.exec("SELECT MAX(CAST(Kode_buku AS UNSIGNED)) FROM Buku"))
            qFatal() << "Error get max id " << idQuery.lastError();

        int maxId = -1;
        if (idQuery.next()) {
            maxId = idQuery.value(0).toInt();
        }

        query.prepare("INSERT INTO Buku("
                      " Kode_buku,"
                      " Judul,"
                      " Pengarang,"
                      " Jml_Buku,"
                      " Kode_Penerbit,"
                      " Harga_Sebulan"
                      ") VALUES ("
                      " :kode,"
                      " :judul,"
                      " :pengarang,"
                      " :jml_buku,"
                      " :kode_penerbit,"
                      " 0"
                      ")");
        query.bindValue(":kode", QString::number(maxId + 1).rightJustified(4, '0'));
    } else {
        query.prepare("UPDATE Buku SET "
                      "Judul = :judul,"
                      "Pengarang = :pengarang,"
                      "Jml_Buku = :jml_buku,"
                      "Kode_penerbit = :kode_penerbit "
                      "WHERE Kode_buku = :kode");
        query.bindValue(":kode", mBookId);
    }

    query.bindValue(":judul", mJudul);
    query.bindValue(":pengarang", mPenulis);
    query.bindValue(":jml_buku", mJumlahBuku);
    query.bindValue(":kode_penerbit", mPenerbitKode);

    if (!query.exec())
        qFatal() << "Error submit " << query.lastError().text();


}
