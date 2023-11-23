#ifndef BASEPEMINJAMANBUKUMODEL_H
#define BASEPEMINJAMANBUKUMODEL_H

#include <Qt>
#include <QDate>

namespace BasePeminjamanBukuModel {
    enum Role {
        KodeBukuRole = Qt::UserRole,
        JudulBukuRole,
        DendaRole
    };

    QHash<int, QByteArray> getRoleNames();
}

#endif // BASEPEMINJAMANBUKUMODEL_H
