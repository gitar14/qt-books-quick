#ifndef BASEPENGADAANBUKUMODEL_H
#define BASEPENGADAANBUKUMODEL_H

#include <Qt>

namespace BasePengadaanBukuModel {
    enum Role {
        KodeBukuRole = Qt::UserRole,
        JumlahRole,
        JudulBukuRole
    };

    QHash<int, QByteArray> getRoleNames();
}

#endif // BASEPENGADAANBUKUMODEL_H
