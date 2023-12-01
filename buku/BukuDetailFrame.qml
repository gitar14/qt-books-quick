import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property BukuViewModel currentViewModel

    signal editClicked()
    signal deleteClicked()


    GridLayout {
        anchors.fill: parent
        columns: 2
        columnSpacing: 16
        visible: currentViewModel.hasSelectedItem

        Label {
            Layout.columnSpan: 2
            text: "Detail Buku"
            font.pixelSize: 24
        }

        Label {
            text: "Kode"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.kode
        }

        Label {
            text: "Judul"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.judul
        }

        Label {
            text: "Penulis"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.penulis
        }

        Label {
            text: "Kategori"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.namaKategori
        }

        Label {
            text: "Penerbit"
        }

        Label{
            text: currentViewModel.selectedData.namaPenerbit
            Layout.fillWidth: true
        }

        Label {
            text: "Tahun Terbit"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedData.tahunTerbit
        }


        Label {
            text: "Jumlah Pengadaan"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedDataJumlah.pengadaan
        }

        Label {
            text: "Jumlah Hilang"
        }

        Label {
           Layout.fillWidth: true
           text: currentViewModel.selectedData.jumlahHilang
        }

        Label {
            text: "Jumlah Tidak Hilang"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedDataJumlah.tidakHilang
        }

        Label {
            text: "Jumlah Dipinjam"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedDataJumlah.dipinjam
        }

        Label {
            text: "Jumlah Tersedia"
        }

        Label {
            Layout.fillWidth: true
            text: currentViewModel.selectedDataJumlah.tersedia
        }

        Rectangle {
            Layout.columnSpan: 2
            Layout.fillHeight: true
        }

        RowLayout {
            Layout.columnSpan: 2


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
        text: "Tidak Ada Data Buku"
        visible: !currentViewModel.hasSelectedItem
    }
}
