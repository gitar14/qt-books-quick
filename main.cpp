#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtSql>
#include <QDir>

#include "kategorimodel.h"
#include "booklistmodel.h"
#include "booklistdetailmodel.h"
#include "penerbitmodel.h"
#include "pengadaanbukumodel.h"
#include "editablepengadaanbukumodel.h"
#include "pengadaanmodel.h"
#include "membermodel.h"
#include "editablepeminjamanbukumodel.h"
#include "connectionmanager.h"
#include "settingsmodel.h"
#include "usermanager.h"
#include "usermodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BookListModel>("my.id.levirs.books", 1, 0, "BookListModel");
    qmlRegisterType<BookListDetailModel>("my.id.levirs.books", 1, 0, "BookListDetailModel");
    qmlRegisterType<KategoriModel>("my.id.levirs.books", 1, 0, "KategoriModel");
    qmlRegisterType<PenerbitModel>("Kelompok7.Perpus", 1, 0, "PenerbitModel");
    qmlRegisterType<PengadaanBukuModel>("Kelompok7.Perpus", 1, 0, "PengadaanBukuModel");
    qmlRegisterType<EditablePengadaanBukuModel>("Kelompok7.Perpus", 1, 0, "EditablePengadaanBukuModel");
    qmlRegisterType<PengadaanModel>("Kelompok7.Perpus", 1, 0, "PengadaanModel");
    qmlRegisterType<MemberModel>("Kelompok7.Perpus", 1, 0, "MemberModel");
    qmlRegisterType<EditablePeminjamanBukuModel>("Kelompok7.Perpus", 1, 0, "EditablePeminjamanBukuModel");
    qmlRegisterType<SettingsModel>("Kelompok7.Perpus", 1, 0, "SettingsModel");
    qmlRegisterType<UserModel>("my.id.levirs.books",1,0,"UserModel");
    qmlRegisterSingletonInstance("Kelompok7.Perpus", 1, 0, "ConnectionManager", ConnectionManager::getInstance());
    qmlRegisterSingletonInstance("Kelompok7.Perpus", 1, 0, "UserManager", UserManager::getInstance());

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("qt-books-qml", "Main");

    return app.exec();
}
