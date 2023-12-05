import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property PengadaanViewModel currentViewModel

    signal editClicked()
    signal deleteClicked()

    ColumnLayout {
        anchors.fill: parent
        visible: currentViewModel.hasSelectedItem

        Text {
            text: "Detail Pengadaan"
            font.pixelSize: 24
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            Layout.leftMargin: -16
            Layout.rightMargin: -16
            Material.background: "transparent"

            TabButton {
                text: "Dasar"
            }

            TabButton {
                text: "Buku"
            }
        }

        StackLayout {
            currentIndex: tabBar.currentIndex
            Layout.topMargin: 8
            Layout.bottomMargin: 8

            ColumnLayout {
                Label {
                    text: "Sumber"
                }

                Label {
                    text: currentViewModel.selectedData.sumber
                    font.bold: true
                }

                Label {
                    text: "Penambah"
                }

                Label {
                    text: currentViewModel.selectedData.userNama
                    font.bold: true
                }

                Label{
                    text: "Tanggal"
                }

                Label{
                    text: Qt.formatDate(currentViewModel.selectedData.tanggalPengadaan, locale, Locale.LongFormat)
                    font.bold: true
                }
            }

            ListView {
                id: bukuListView
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: currentViewModel.selectedBukuList
                spacing: 8
                clip: true

                delegate: Pane {
                    width: ListView.view.width
                    padding: 16

                    background: Rectangle {
                        border.color: "#dedede"
                        border.width: 1
                        radius: 16
                    }

                    contentItem: ColumnLayout {
                        Label {
                            text: modelData.judul
                            font.bold: true
                        }
                        Label {
                            text: modelData.jumlah
                        }
                    }
                }
            }
        }

        Row {
            Layout.alignment: Qt.AlignRight
            spacing: 8

            Button {
                text: "Edit"
                onClicked: editClicked()
            }

            Button {
                text: "Hapus"
                onClicked: deleteClicked()
                highlighted: true
                Material.accent: Material.Red
            }
        }

    }

    Label {
        visible: !currentViewModel.hasSelectedItem
        text: "Tidak ada pengadaan yang terpilih"
    }
}
