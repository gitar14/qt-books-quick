#ifndef SQLHELPER_H
#define SQLHELPER_H

#include <Qt>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace SQLHelper {
    template <typename T> QString generateArrayBinds(QString prefix, const QList<T>& list, QHash<QString, QVariant> &binds)
    {
        QStringList bindResults;
        for (qsizetype i = 0; i < list.length(); i++) {
            QString name = prefix + QString::number(i);
            bindResults.push_back(name);
            binds[name] = list.at(i);
        }

        return bindResults.join(",");
    }

    void applyBindMaps(QSqlQuery& query, const QHash<QString, QVariant>& binds);
    void initializeDatabase(QSqlDatabase& db);
    void clearDatabase(QSqlDatabase& db);

    /**
     * @brief createUpsertQuery Create upsert query
     * @param db
     * @param insertQuery Insert query tanpa INSERT INTO
     * @param updateQuery Update query tanpa UPDATE SET
     * @param candidateKey Kunci yang menentukan keunikan (hanya untuk SQLite)
     * @return Query untuk upsert
     */
    QString createUpsertQuery(const QSqlDatabase &db, const QString& insertQuery, const QString& updateQuery, const QStringList& candidateKey);
}

#endif // SQLHELPER_H
