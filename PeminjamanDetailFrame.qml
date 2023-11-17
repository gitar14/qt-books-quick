import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

Frame {
    property string peminjamanKode: ""
    property string peminjamanMemberKode: ""
    property string peminjamanMemberNama: ""
    property date peminjamanTanggal: new Date()
    property int peminjamanLama: 0
    property date peminjamanTanggalTenggat: new Date()
    property date peminjamanTanggalPengembalian: new Date()
    property bool peminjamanSudahDikembalikan: false
    required property PeminjamanBukuModel peminjamanBukuModel

    signal editClicked()
    signal deleteClicked()
    signal tandaiDikembalikanClicked()
    signal tandaiBelumDikembalikanClicked()

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
            text: "Tanggal"
        }

        Label{
            text: Qt.formatDate(peminjamanTanggal, locale, locale.LongFormat)
            Layout.fillWidth: true

        }

        Label{
            text: "Lama Peminjaman"
        }

        Label{
            text: peminjamanLama + " hari"
            Layout.fillWidth: true
        }

        Label {
            text: "Tanggal Tenggat"
        }

        Label {
            text: Qt.formatDate(peminjamanTanggal, locale, locale.LongFormat)
            Layout.fillWidth: true
        }

        Label {
            text: "Status"
        }

        Label {
            Layout.fillWidth: true
            text: peminjamanSudahDikembalikan ? "Sudah Dikembalikan" : "Belum Dikembalikan"
        }

        Label {
            visible: peminjamanSudahDikembalikan
            text: "Tanggal Pengembalian"
        }

        Label {
            visible: peminjamanSudahDikembalikan
            Layout.fillWidth: true
            text: Qt.formatDate(peminjamanTanggalPengembalian, locale, locale.LongFormat)
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

        Button {
            visible: !peminjamanSudahDikembalikan
            text: "Tandai Dikembalikan"
            onClicked: tandaiDikembalikanClicked()
            Layout.columnSpan: 2
        }

        Button {
            visible: peminjamanSudahDikembalikan
            text: "Tandai Belum Dikembalikan"
            onClicked: tandaiBelumDikembalikanClicked()
            Layout.columnSpan: 2
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
