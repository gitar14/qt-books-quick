import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

Frame {
    property string peminjamanKode: ""
    property string peminjamanMemberKode: ""
    property string peminjamanMemberNama: ""
    property int peminjamanLama: 0
    property date peminjamanTanggal: new Date()
    required property PeminjamanBukuModel peminjamanBukuModel

    signal editClicked()
    signal deleteClicked()

    Layout.minimumWidth: 300
    Layout.maximumWidth: 300
    Layout.fillHeight: true
    Layout.rightMargin: 16
    Layout.topMargin: 16
    Layout.bottomMargin: 16
    padding: 16

    background: Rectangle {
        border.color: "#dedede"
        border.width: 1
        radius: 16
    }

    GridLayout{
        anchors.fill: parent
        columnSpacing: 16
        visible: peminjamanKode !=""
        columns: 2

        Text {
            Layout.columnSpan: 2
            text: "Detail Peminjaman"
            font.pixelSize: 24
        }

        Label{
            text: "Nama Member"
        }

        Label{
            text: peminjamanMemberNama
            Layout.fillWidth: true
        }
        Label{
            text: "Tanggal Peminjaman"
        }

        Label{
            text: Qt.formatDate(peminjamanTanggal, locale, locale.LongFormat)
            Layout.fillWidth: true

        }

        Label{
            text: "Lama Peminjaman"
        }

        Label{
            text: peminjamanLama
            Layout.fillWidth: true
        }

        ListView {
            Layout.columnSpan: 2
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: peminjamanBukuModel
            spacing: 8

            delegate: Pane {
                width: ListView.view.width
                padding: 16

                background: Rectangle {
                    border.color: "#dedede"
                    border.width: 1
                    radius: 16
                }

                contentItem: Label {
                    text: model.judulBuku
                }
            }
        }

        Row {
            Layout.columnSpan: 2
            Layout.fillWidth: true
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
}
