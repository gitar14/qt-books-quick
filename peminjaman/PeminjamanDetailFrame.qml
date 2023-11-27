import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property PeminjamanViewModel currentViewModel

    signal editClicked()
    signal deleteClicked()
    signal tandaiDikembalikanClicked()
    signal tandaiBelumDikembalikanClicked()

    GridLayout {
        anchors.fill: parent
        columnSpacing: 16
        visible: currentViewModel.hasSelectedItem
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
            text: currentViewModel.selectedData.namaMember
            Layout.fillWidth: true
        }
        Label{
            text: "Tanggal"
        }

        Label{
            text: Qt.formatDate(currentViewModel.selectedData.tanggalPeminjaman, locale, locale.LongFormat)
            Layout.fillWidth: true
        }

        Label{
            text: "Lama Peminjaman"
        }

        Label{
            text: currentViewModel.selectedData.lamaPeminjaman + " hari"
            Layout.fillWidth: true
        }

        Label {
            text: "Tanggal Tenggat"
        }

        Label {
            text: Qt.formatDate(currentViewModel.selectedData.tenggatPengembalian, locale, locale.LongFormat)
            Layout.fillWidth: true
        }

        Label {
            text: "Status"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.sudahDikembalikan ? "Sudah Dikembalikan" : "Belum Dikembalikan"
        }

        Label {
            visible: currentViewModel.selectedData.sudahDikembalikan
            text: "Tanggal Pengembalian"
        }

        Label {
            visible: currentViewModel.selectedData.sudahDikembalikan
            Layout.fillWidth: true
            text: Qt.formatDate(currentViewModel.selectedData.tanggalPengembalian, locale, locale.LongFormat)
        }

        Label {
            visible: currentViewModel.selectedData.sudahDikembalikan
            text: "Denda Keterlambatan"
        }

        Label {
            visible: currentViewModel.selectedData.sudahDikembalikan
            text: currentViewModel.selectedDenda.totalDendaTerlambat
            Layout.fillWidth: true
        }

        Label {
            visible: currentViewModel.selectedData.sudahDikembalikan
            text: "Total Denda"
        }

        Label {
            visible: currentViewModel.selectedData.sudahDikembalikan
            text: currentViewModel.selectedDenda.totalDenda
            Layout.fillWidth: true
        }


        ListView {
            Layout.columnSpan: 2
            Layout.fillHeight: true
            Layout.fillWidth: true
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

                contentItem: Column {
                    Label {
                        text: modelData.judul
                    }

                    Label {
                        visible: modelData.denda
                        text: "Denda: " + modelData.denda
                    }
                }
            }
        }

        Button {
            visible: !currentViewModel.selectedData.sudahDikembalikan
            text: "Tandai Dikembalikan"
            onClicked: tandaiDikembalikanClicked()
            Layout.columnSpan: 2
        }

        Button {
            visible: currentViewModel.selectedData.sudahDikembalikan
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
