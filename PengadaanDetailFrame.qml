import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

BaseDetailFrame {
    property string pengadaanKode: ""
    property string pengadaanSumber: ""
    property date pengadaanTanggal: new Date()
    required property PengadaanBukuModel pengadaanBukuModel

    signal editClicked()
    signal deleteClicked()

    GridLayout {
        anchors.fill: parent
        columnSpacing: 16
        visible: pengadaanKode != ""
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
            text: pengadaanKode
            Layout.fillWidth: true
        }

        Label {
            text: "Sumber"
        }

        Label {
            text: pengadaanSumber
            Layout.fillWidth: true
        }

        Label{
            text: "Tanggal"
        }

        Label{
            text: Qt.formatDate(pengadaanTanggal, locale, locale.LongFormat)
            Layout.fillWidth: true
        }

        Label {
            text: pengadaanBukuModel.count > 0 ?  "Buku" : "Buku kosong"
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignHCenter

        }

        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 2
            model: pengadaanBukuModel
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
                        text: model.judulBuku
                    }
                    Label {
                        text: model.jumlah
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
        visible: pengadaanDetailFrame.detailSumber == ""
        text: "Tidak ada item yang terpilih"
    }
}
