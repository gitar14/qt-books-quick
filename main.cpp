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

#define PACKAGE "Kelompok7.Perpus"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BookListModel>(PACKAGE, 1, 0, "BookListModel");
    qmlRegisterType<BookListDetailModel>(PACKAGE, 1, 0, "BookListDetailModel");
    qmlRegisterType<KategoriModel>(PACKAGE, 1, 0, "KategoriModel");
    qmlRegisterType<PenerbitModel>(PACKAGE, 1, 0, "PenerbitModel");
    qmlRegisterType<PengadaanBukuModel>(PACKAGE, 1, 0, "PengadaanBukuModel");
    qmlRegisterType<EditablePengadaanBukuModel>(PACKAGE, 1, 0, "EditablePengadaanBukuModel");
    qmlRegisterType<PengadaanModel>(PACKAGE, 1, 0, "PengadaanModel");
    qmlRegisterType<MemberModel>(PACKAGE, 1, 0, "MemberModel");
    qmlRegisterType<EditablePeminjamanBukuModel>(PACKAGE, 1, 0, "EditablePeminjamanBukuModel");
    qmlRegisterType<UserModel>(PACKAGE,1,0,"UserModel");
    qmlRegisterType<SettingsModel>(PACKAGE, 1, 0, "SettingsModel");
    qmlRegisterSingletonInstance(PACKAGE, 1, 0, "ConnectionManager", ConnectionManager::getInstance());
    qmlRegisterSingletonInstance(PACKAGE, 1, 0, "UserManager", UserManager::getInstance());

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("qt-books-qml", "Main");

    return app.exec();
}
