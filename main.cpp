#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtSql>
#include <QDir>

#include "kategoriviewmodel.h"
#include "kategorieditviewmodel.h"
#include "kategorifiltermodel.h"
#include "booklistmodel.h"
#include "booklistdetailmodel.h"
#include "penerbitviewmodel.h"
#include "penerbiteditviewmodel.h"
#include "penerbitfiltermodel.h"
#include "pengadaanbukumodel.h"
#include "editablepengadaanbukumodel.h"
#include "pengadaanmodel.h"
#include "membermodel.h"
#include "editablepeminjamanbukumodel.h"
#include "connectionmanager.h"
#include "settingsmodel.h"
#include "usermanager.h"
#include "usermodel.h"
#include "peminjamanmodel.h"
#include "peminjamanbukumodel.h"
#include "peminjamandendamodel.h"
#include "texthighlighter.h"

#define PACKAGE "Kelompok7.Perpus"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BookListModel>(PACKAGE, 1, 0, "BookListModel");
    qmlRegisterType<BookListDetailModel>(PACKAGE, 1, 0, "BookListDetailModel");
    qmlRegisterType<KategoriViewModel>(PACKAGE, 1, 0, "KategoriViewModel");
    qmlRegisterType<KategoriEditViewModel>(PACKAGE, 1, 0, "KategoriEditViewModel");
    qmlRegisterType<KategoriFilterModel>(PACKAGE, 1, 0, "KategoriFilterModel");
    qmlRegisterType<PenerbitViewModel>(PACKAGE, 1, 0, "PenerbitViewModel");
    qmlRegisterType<PenerbitEditViewModel>(PACKAGE, 1, 0, "PenerbitEditViewModel");
    qmlRegisterType<PenerbitFilterModel>(PACKAGE, 1, 0, "PenerbitFilterModel");
    qmlRegisterType<PengadaanBukuModel>(PACKAGE, 1, 0, "PengadaanBukuModel");
    qmlRegisterType<EditablePengadaanBukuModel>(PACKAGE, 1, 0, "EditablePengadaanBukuModel");
    qmlRegisterType<PengadaanModel>(PACKAGE, 1, 0, "PengadaanModel");
    qmlRegisterType<MemberModel>(PACKAGE, 1, 0, "MemberModel");
    qmlRegisterType<EditablePeminjamanBukuModel>(PACKAGE, 1, 0, "EditablePeminjamanBukuModel");
    qmlRegisterType<UserModel>(PACKAGE,1,0,"UserModel");
    qmlRegisterType<PeminjamanModel>(PACKAGE, 1, 0, "PeminjamanModel");
    qmlRegisterType<PeminjamanBukuModel>(PACKAGE, 1, 0, "PeminjamanBukuModel");
    qmlRegisterType<PeminjamanDendaModel>(PACKAGE, 1, 0, "PeminjamanDendaModel");
    qmlRegisterType<SettingsModel>(PACKAGE, 1, 0, "SettingsModel");
    qmlRegisterSingletonInstance(PACKAGE, 1, 0, "ConnectionManager", ConnectionManager::getInstance());
    qmlRegisterSingletonInstance(PACKAGE, 1, 0, "UserManager", UserManager::getInstance());
    qmlRegisterSingletonInstance(PACKAGE, 1, 0, "TextHighlighter", TextHighlighter::getInstance());

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("qt-books-qml", "Main");

    return app.exec();
}
