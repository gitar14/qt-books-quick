#ifndef SAFEOBJECTLIST_H
#define SAFEOBJECTLIST_H

#include <QList>
#include <concepts>

template <typename T>
concept IsQObject = std::is_base_of<QObject, T>::value;

template <IsQObject T>
class SafeObjectList : public QList<T*> {
    using ListType = QList<T*>;

    void deleteAllItems() {
        for (int i = 0; i < ListType::count(); i++) {
            ListType::at(i)->deleteLater();
        }
    }
public:
    ~SafeObjectList() {
        deleteAllItems();
    }

    void clear() {
        deleteAllItems();
        ListType::clear();
    }

    void operator =(const ListType& other) {
        clear();
        for (int i = 0; i < other.count(); i++) {
            ListType::append(other.at(i));
        }
    }
};

#endif // SAFEOBJECTLIST_H
