import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    leftPadding: sidebarRadius

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: sidebarRadius

            RoundButton {
                Material.background: "transparent"
                icon.source: "qrc:/icons/arrow-back.svg"
                icon.width: 24
                icon.height: 24
                onClicked: dashboardStackView.pop()
            }

            Label {
                Layout.fillWidth: true
                text: "Tentang"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 20
            }
        }
    }

    Flickable {
        width: Math.min(parent.width - 32, 512)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.margins: 16
        contentHeight: rootLayout.height

        ColumnLayout {
            width: parent.width
            id: rootLayout
            spacing: 8

            Label {
                font.pixelSize: 24
                text: "QuickPerpus"
                Layout.alignment: Qt.AlignCenter
            }

            Label {
                font.pixelSize: 16
                text: "Pengembang"
            }

            Frame {
                Layout.fillWidth: true
                background: CardBackground {}

                ColumnLayout {
                    anchors.fill: parent

                    Repeater {
                        model: ListModel {
                            ListElement {
                                name: "Levi Rizki Saputra"
                                avatar: "https://avatars.githubusercontent.com/u/42236775?s=96&v=4"
                                ghUsername: "levirs565"
                            }

                            ListElement {
                                name: "Dida Attallah E"
                                avatar: "https://avatars.githubusercontent.com/u/149646493?s=64&v=4"
                                ghUsername: "savze7"
                            }

                            ListElement {
                                name: "Narindera Jati P"
                                avatar: "https://avatars.githubusercontent.com/u/147364376?s=64&v=4"
                                ghUsername: "jep333"
                            }

                            ListElement {
                                name: "Raden Revano"
                                avatar: "https://avatars.githubusercontent.com/u/150409296?s=64&v=4"
                                ghUsername: "vanoathalla"
                            }

                            ListElement {
                                name: "Gita Ristya"
                                avatar: "https://avatars.githubusercontent.com/u/149128473?s=64&v=4"
                                ghUsername: "gitar14"
                            }
                        }

                        delegate: AboutItemDelegate {
                            required property string name
                            required property string avatar
                            required property string ghUsername
                            url: "https://github.com/" + ghUsername
                            subtitle: "GitHub @" + ghUsername
                            imageSource: avatar
                            title: name
                        }
                    }
                }
            }

            Label {
                font.pixelSize: 16
                text: "Kredit"
            }

            Frame {
                Layout.fillWidth: true
                background: CardBackground {}

                contentItem: ItemDelegate {
                    width: parent.width
                    text: "Animasi Splash Screen oleh Taras Chernenko"
                    onClicked: {
                        Qt.openUrlExternally("https://lottiefiles.com/animations/books-CIVKrwHpmm")
                    }
                }
            }

            Label {
                font.pixelSize: 16
                text: "Pustaka"
            }

            Frame {
                Layout.fillWidth: true

                background: CardBackground {}

                contentItem: ColumnLayout {
                    Repeater {
                        model: ListModel {
                            ListElement {
                                url: "https://www.qt.io/"
                                imageSource: "qrc:/icons/qt.png"
                                title: "Qt"
                                subtitle: "Framework Pengembangan Perangkat Lunak"
                            }

                            ListElement {
                                url: "https://botan.randombit.net/"
                                imageSource: ""
                                title: "Botan"
                                subtitle: "Library kriptografi"
                            }
                        }

                        delegate: AboutItemDelegate {}
                    }
                }
            }
        }
    }
}
