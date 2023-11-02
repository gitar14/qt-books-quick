#ifndef MEMBERMODEL_H
#define MEMBERMODEL_H

#include <QSqlQueryModel>
#include <QQmlEngine>

class MemberModel : public QSqlQueryModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MemberModel(QObject *parent = nullptr);

};

#endif // MEMBERMODEL_H
