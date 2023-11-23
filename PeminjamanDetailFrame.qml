import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

BaseDetailFrame {
    property int peminjamanKode: -1
    property int peminjamanMemberKode: -1
    property string peminjamanMemberNama: ""
    property date peminjamanTanggal: new Date()
    property int peminjamanLama: 0
    property date peminjamanTanggalTenggat: new Date()
    property date peminjamanTanggalPengembalian: new Date()
    property bool peminjamanSudahDikembalikan: false
    property int peminjamanDendaPerHari: 0
    required property PeminjamanBukuModel peminjamanBukuModel

    signal editClicked()
    signal deleteClicked()
    signal tandaiDikembalikanClicked()
    signal tandaiBelumDikembalikanClicked()

    PeminjamanDendaModel {
        id: peminjamanDendaCalculator
        dendaTerlambatPerBuku: peminjamanDendaPerHari
        dendaTambahanBukuList: peminjamanBukuModel.dendaList
        tanggalPengembalian: peminjamanTanggalPengembalian
        tenggatPengembalian: peminjamanTanggalTenggat
    }

    GridLayout {
        anchors.fill: parent
        columnSpacing: 16
        visible: peminjamanKode != -1
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
            text: Qt.formatDate(peminjamanTanggalTenggat, locale, locale.LongFormat)
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

        Label {
            visible: peminjamanSudahDikembalikan
            text: "Denda Keterlambatan"
        }

        Label {
            visible: peminjamanSudahDikembalikan
            text: peminjamanDendaCalculator.totalDendaTerlambat
            Layout.fillWidth: true
        }

        Label {
            visible: peminjamanSudahDikembalikan
            text: "Total Denda"
        }

        Label {
            visible: peminjamanSudahDikembalikan
            text: peminjamanDendaCalculator.totalDenda
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

                contentItem: Column {
                    Label {
                        text: model.judulBuku
                    }

                    Label {
                        visible: model.denda
                        text: "Denda: " + model.denda
                    }
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
