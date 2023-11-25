#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtSql>
#include <QDir>

#include "kategoriviewmodel.h"
#include "kategorieditviewmodel.h"
#include "bukupilihviewmodel.h"
#include "bukuviewmodel.h"
#include "bukueditviewmodel.h"
#include "penerbitviewmodel.h"
#include "penerbiteditviewmodel.h"
#include "pengadaanviewmodel.h"
#include "pengadaaneditviewmodel.h"
#include "membermodel.h"
#include "editablepeminjamanbukumodel.h"
#include "connectionmanager.h"
#include "settingsmodel.h"
#include "usermanager.h"
#include "usermodel.h"
#include "peminjamanmodel.h"
#include "peminjamanbukumodel.h"
#include "peminjamandendamodel.h"
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
    qmlRegisterType<MemberModel>(PACKAGE, 1, 0, "MemberModel");
    qmlRegisterType<EditablePeminjamanBukuModel>(PACKAGE, 1, 0, "EditablePeminjamanBukuModel");
    qmlRegisterType<UserModel>(PACKAGE,1,0,"UserModel");
    qmlRegisterType<PeminjamanModel>(PACKAGE, 1, 0, "PeminjamanModel");
    qmlRegisterType<PeminjamanBukuModel>(PACKAGE, 1, 0, "PeminjamanBukuModel");
    qmlRegisterType<PeminjamanDendaModel>(PACKAGE, 1, 0, "PeminjamanDendaModel");
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
