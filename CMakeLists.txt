cmake_minimum_required(VERSION 3.16)

project(qt-books-qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Sql QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appqt-books-qml
    main.cpp
)

qt_add_qml_module(appqt-books-qml
    URI qt-books-qml
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES kategorimodel.h kategorimodel.cpp
    QML_FILES KategoriScreen.qml
    SOURCES booklistmodel.h booklistmodel.cpp
    QML_FILES BukuScreen.qml
    SOURCES booklistdetailmodel.h booklistdetailmodel.cpp
    SOURCES booklistdetailmodel.h booklistdetailmodel.cpp
    SOURCES
    QML_FILES PenerbitScreen.qml
    SOURCES penerbitmodel.h penerbitmodel.cpp
    SOURCES editablepengadaanbukumodel.h editablepengadaanbukumodel.cpp
    QML_FILES PengadaanScreen.qml
    SOURCES pengadaanmodel.h pengadaanmodel.cpp
    SOURCES pengadaanbukumodel.h pengadaanbukumodel.cpp
    SOURCES basepengadaanbukumodel.h
    SOURCES basepengadaanbukumodel.cpp
    QML_FILES MemberScreen.qml
    SOURCES membermodel.h membermodel.cpp
    QML_FILES PeminjamanList.qml
    QML_FILES FloatingActionButton.qml
    QML_FILES PenerbitEditDialog.qml
    QML_FILES PenerbitDetailFrame.qml
    QML_FILES PenerbitList.qml
    QML_FILES KategoriEditDialog.qml
    QML_FILES KategoriDetailFrame.qml
    QML_FILES KategoriList.qml
    QML_FILES MemberEditDialog.qml
    QML_FILES MemberDetailFrame.qml
    QML_FILES MemberList.qml
    QML_FILES DateField.qml
    QML_FILES BukuEditDialog.qml
    QML_FILES BukuDetailFrame.qml
    QML_FILES BukuList.qml
    QML_FILES PengadaanEditDialog.qml
    QML_FILES BukuPilihDialog.qml
    QML_FILES PengadaanDetailFrame.qml
    QML_FILES PengadaanList.qml
    QML_FILES BukuListView.qml
    SOURCES sqlhelper.h
    SOURCES sqlhelper.cpp
    SOURCES basepeminjamanbukumodel.h
    SOURCES basepeminjamanbukumodel.cpp
    SOURCES editablepeminjamanbukumodel.h editablepeminjamanbukumodel.cpp
    SOURCES peminjamanbukumodel.h peminjamanbukumodel.cpp
    SOURCES peminjamanmodel.h peminjamanmodel.cpp
    RESOURCES resources.qrc
    QML_FILES SearchField.qml
    QML_FILES CardDelegate.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqt-books-qml PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqt-books-qml
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqt-books-qml
    PRIVATE Qt6::Quick Qt6::Sql Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appqt-books-qml
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
