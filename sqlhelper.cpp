#include "sqlhelper.h"
#include <QList>
#include <QHash>
#include <QVariant>

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

}
