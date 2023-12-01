#ifndef SCOPEDOBJECTLIST_H
#define SCOPEDOBJECTLIST_H

#include <QList>
#include <concepts>

template <typename T>
concept IsQObject = std::is_base_of<QObject, T>::value;

template <IsQObject T>
class ScopedObjectList : public QList<T*> {
    using ListType = QList<T*>;

    void deleteAllItems() {
        deleteItems(0, ListType::count());
    }

    void deleteItems(qsizetype from, qsizetype count) {
        for (int i = 0; i < count; i++) {
            ListType::at(from + i)->deleteLater();
        }
    }
public:
    ~ScopedObjectList() {
        deleteAllItems();
    }

    void remove(qsizetype i, qsizetype n = 1) {
        deleteItems(i, n);
        ListType::remove(i, n);
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

#endif // SCOPEDOBJECTLIST_H
