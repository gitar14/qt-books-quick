import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    property int selectedScreenIndex: 0

    function setSelectedScreenIndex(index) {
        if (selectedScreenIndex === index) return
        selectedScreenIndex = index
        dashboardStackView.replace(screenList.get(index).view)
    }

    ListModel {
        id: screenList
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

    StackView {
        id: dashboardStackView
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.leftMargin: sidebarWidth - sidebarRadius

        initialItem: screenList.get(0).view

        replaceEnter: Transition {
            NumberAnimation {
                properties: "opacity"
                from: 0
                to: 0
                duration: 0
            }

            SequentialAnimation {
                PauseAnimation {
                    duration: 250
                }
                OpacityAnimator {
                    from: 0
                    to: 1
                    duration: 250
                }
            }
        }
        replaceExit: Transition {
            OpacityAnimator {
                from: 1
                to: 0
                duration: 100
            }
        }
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
                    model: screenList

                    delegate: ItemDelegate {
                        id: sidebarDelegate
                        width: parent.width
                        onClicked: setSelectedScreenIndex(index)
                        highlighted: selectedScreenIndex === index

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
