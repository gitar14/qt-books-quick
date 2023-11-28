import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property PengadaanViewModel currentViewModel

    signal editClicked()
    signal deleteClicked()

    GridLayout {
        anchors.fill: parent
        columnSpacing: 16
        visible: currentViewModel.hasSelectedItem
        columns: 2

        Text {
            Layout.columnSpan: 2
            text: "Pengadaan Detail"
            font.pixelSize: 24
        }

        Label {
            text: "Kode"
        }

        Label {
            text: currentViewModel.selectedData.kode
            Layout.fillWidth: true
        }

        Label {
            text: "Pennambah"
        }

        Label {
            text: currentViewModel.selectedData.userNama
            Layout.fillWidth: true
        }

        Label {
            text: "Sumber"
        }

        Label {
            text: currentViewModel.selectedData.sumber
            Layout.fillWidth: true
        }

        Label{
            text: "Tanggal"
        }

        Label{
            text: Qt.formatDate(currentViewModel.selectedData.tanggalPengadaan, locale, locale.LongFormat)
            Layout.fillWidth: true
        }

        Label {
            text: bukuListView.count > 0 ? "Buku" : "Buku Kosong"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignHCenter
        }

        ListView {
            id: bukuListView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 2
            model: currentViewModel.selectedBukuList
            spacing: 8

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
                    }
                    Label {
                        text: modelData.jumlah
                    }
                }
            }
        }

        Row {
            Layout.columnSpan: 2
            spacing: 8

            Button {
                text: "Edit"
                onClicked: editClicked()
            }

            Button {
                text: "Hapus"
                onClicked: deleteClicked()
            }
        }

    }

    Label {
        visible: !currentViewModel.hasSelectedItem
        text: "Tidak ada item yang terpilih"
    }
}
