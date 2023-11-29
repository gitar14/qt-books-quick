import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    property string currentView: "buku/BukuScreen.qml"

    Loader {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.leftMargin: sidebarWidth - sidebarRadius

        source: currentView
    }

    Frame {
        width: sidebarWidth
        height: parent.height
        background: Rectangle {
            width: parent.width + radius
            x: -radius
            radius: sidebarRadius
            border.color: "#dedede"
        }
        padding: 0

        ColumnLayout {
            anchors.fill: parent
            
            Frame {
                Layout.leftMargin: 16
                Layout.rightMargin: 16
                Layout.fillWidth: true
                background: Rectangle {
                    radius: 8
                    border.width: 1
                    border.color: "#dedede"
                }

                RowLayout {
                    anchors.fill: parent

                    Image {
                        source: "qrc:/icons/person-circle-black.svg"
                    }

                    Label {
                        Layout.fillWidth: true
                        text: UserManager.loggedUser.nama
                    }

                }
            }

            Column {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop

                Repeater {

                    model: ListModel {
                        Component.onCompleted: {
                            if (UserManager.loggedUser.role != UserData.AdminRole) {
                                remove(count - 2)
                            }
                        }

                        ListElement {
                            name: "Buku"
                            view: "buku/BukuScreen.qml"
                        }
                        ListElement {
                            name: "Kategori"
                            view: "kategori/KategoriScreen.qml"
                        }
                        ListElement{
                            name : "Penerbit"
                            view : "penerbit/PenerbitScreen.qml"
                        }
                        ListElement{
                            name : "Member"
                            view : "member/MemberScreen.qml"
                        }
                        ListElement {
                            name: "Pengadaan Buku"
                            view: "pengadaan/PengadaanScreen.qml"
                        }
                        ListElement {
                            name: "Peminjaman Buku"
                            view: "peminjaman/PeminjamanScreen.qml"
                        }
                        ListElement {
                            name: "Pegawai"
                            view: "user/UserScreen.qml"
                        }

                        ListElement {
                            name: "Pengaturan"
                            view: "SettingsScreen.qml"
                        }
                    }

                    delegate: ItemDelegate {
                        id: sidebarDelegate
                        width: parent.width
                        onClicked: currentView = view
                        highlighted: currentView === view

                        contentItem: Label {
                            text: name
                            font.bold: true
                            verticalAlignment: Qt.AlignVCenter
                            color: sidebarDelegate.highlighted ?
                                       sidebarDelegate.Material.primary :
                                       sidebarDelegate.Material.foreground
                        }


                        background: Rectangle {
                            implicitHeight: sidebarDelegate.Material.delegateHeight
                            x: -sidebarRadius
                            width: parent.width + sidebarRadius

                            color: sidebarDelegate.highlighted ?
                                       Qt.alpha(Material.shade(sidebarDelegate.Material.primary, Material.Shade500), 0.12)
                                     : "transparent"
                            radius: 32

                            Ripple {
                                width: parent.width
                                height: parent.height
                                clip: true
                                clipRadius: 32
                                pressed: sidebarDelegate.pressed
                                anchor: sidebarDelegate
                                active: enabled &&
                                        (sidebarDelegate.down || sidebarDelegate.visualFocus || sidebarDelegate.hovered)
                                color: sidebarDelegate.Material.rippleColor
                            }

                        }
                    }
                }
            }
        }
    }
}
