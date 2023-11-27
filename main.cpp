#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtSql>
#include <QDir>

#include "userloginviewmodel.h"
#include "kategoriviewmodel.h"
#include "kategorieditviewmodel.h"
#include "bukupilihviewmodel.h"
#include "bukuviewmodel.h"
#include "bukueditviewmodel.h"
#include "penerbitviewmodel.h"
#include "penerbiteditviewmodel.h"
#include "pengadaanviewmodel.h"
#include "pengadaaneditviewmodel.h"
#include "memberpilihviewmodel.h"
#include "memberviewmodel.h"
#include "membereditviewmodel.h"
#include "connectionmanager.h"
#include "settingsmodel.h"
#include "usermanager.h"
#include "userbuatadminviewmodel.h"
#include "userpegawaiviewmodel.h"
#include "userpegawaieditviewmodel.h"
#include "peminjamaneditviewmodel.h"
#include "peminjamanviewmodel.h"
#include "pengembalianviewmodel.h"
#include "textfielddata.h"
#include "combofielddata.h"
#include "texthighlighter.h"

#define PACKAGE "Kelompok7.Perpus"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BukuPilihViewModel>(PACKAGE, 1, 0, "BukuPilihViewModel");
    qmlRegisterType<BukuViewModel>(PACKAGE, 1, 0, "BukuViewModel");
    qmlRegisterType<BukuEditViewModel>(PACKAGE, 1, 0, "BukuEditViewModel");
    qmlRegisterType<KategoriViewModel>(PACKAGE, 1, 0, "KategoriViewModel");
    qmlRegisterType<KategoriEditViewModel>(PACKAGE, 1, 0, "KategoriEditViewModel");
    qmlRegisterType<PenerbitViewModel>(PACKAGE, 1, 0, "PenerbitViewModel");
    qmlRegisterType<PenerbitEditViewModel>(PACKAGE, 1, 0, "PenerbitEditViewModel");
    qmlRegisterType<PengadaanViewModel>(PACKAGE, 1, 0, "PengadaanViewModel");
    qmlRegisterType<PengadaanEditViewModel>(PACKAGE, 1, 0, "PengadaanEditViewModel");
    qmlRegisterType<MemberPilihViewModel>(PACKAGE, 1, 0, "MemberPilihViewModel");
    qmlRegisterType<MemberViewModel>(PACKAGE, 1, 0, "MemberViewModel");
    qmlRegisterType<MemberEditViewModel>(PACKAGE, 1, 0, "MemberEditViewModel");
    qmlRegisterType<UserPegawaiViewModel>(PACKAGE,1,0, "UserPegawaiViewModel");
    qmlRegisterType<UserPegawaiEditViewModel>(PACKAGE,1,0, "UserPegawaiEditViewModel");
    qmlRegisterType<UserBuatAdminViewModel>(PACKAGE,1,0,"UserBuatAdminViewModel");
    qmlRegisterType<UserLoginViewModel>(PACKAGE, 1, 0, "UserLoginViewModel");
    qmlRegisterType<PeminjamanViewModel>(PACKAGE, 1, 0, "PeminjamanViewModel");
    qmlRegisterType<PeminjamanEditViewModel>(PACKAGE, 1, 0, "PeminjamanEditViewModel");
    qmlRegisterType<PengembalianViewModel>(PACKAGE, 1, 0, "PengembalianViewModel");
    qmlRegisterType<SettingsModel>(PACKAGE, 1, 0, "SettingsModel");
    qmlRegisterType<TextFieldData>(PACKAGE, 1, 0, "TextFieldData");
    qmlRegisterType<ComboFieldData>(PACKAGE, 1, 0, "ComboFieldData");
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
