#include "booklistdetailmodel.h"

#include <QtSql>

BookListDetailModel::BookListDetailModel(QObject *parent)
    : QObject{parent},
    mBookId("")
{
}

QString BookListDetailModel::bookId()
{
    return mBookId;
}

void BookListDetailModel::setBookId(const QString &Id)
{
    this->mBookId = Id;
    QSqlQuery query;
    query.prepare(
        "SELECT Buku.*, Penerbit.Nm_penerbit FROM Buku "
        "JOIN Penerbit on Penerbit.Kode_Penerbit = Buku.Kode_Penerbit "
        "WHERE Buku.Kode_buku = :kode"
        );
    query.bindValue(":kode", mBookId);

    if (!query.exec())
        qFatal() << query.lastError().text();

    if (query.next()) {
        QSqlRecord record = query.record();
        mJudul = record.value("Judul").toString();
        mPenulis = record.value("Pengarang").toString();
        mJumlahBuku = record.value("Jml_buku").toInt();
        mKodePenerbit = record.value("Kode_penerbit").toString();
        mNamaPenerbit = record.value("Nm_penerbit").toString();
    } else {
        mJudul = "";
        mPenulis = "";
        mJumlahBuku = 0;
        mKodePenerbit = "";
        mNamaPenerbit = "";
    }
    emit bookIdChanged();
}

QString BookListDetailModel::judul()
{
    return mJudul;
}

QString BookListDetailModel::penulis()
{
    return mPenulis;
}

int BookListDetailModel::jumlahBuku()
{
    return mJumlahBuku;
}

QString BookListDetailModel::kodePenerbit()
{
    return mKodePenerbit;
}

QString BookListDetailModel::namaPenerbit()
{
    return mNamaPenerbit;
}
