import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

BaseDetailFrame {
    property int bukuKode: -1
    property string bukuJudul: ""
    property string bukuPenulis: ""
    property string bukuKategori: ""
    property string bukuPenerbit: ""
    property int bukuJumlahPengadaan: 0
    property int bukuJumlahHilang: 0
    property int bukuJumlahDipinjam: 0
    property int bukuTahunTerbit: 0

    signal editClicked()
    signal deleteClicked()


    GridLayout {
        anchors.fill: parent
        columns: 2
        columnSpacing: 16
        visible: bukuKode != -1

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
            text: bukuKode
        }

        Label {
            text: "Judul"
        }

        Label {
            Layout.fillWidth: true
            text: bukuJudul
        }

        Label {
            text: "Penulis"
        }

        Label {
            Layout.fillWidth: true
            text: bukuPenulis
        }

        Label {
            text: "Kategori"
        }

        Label {
            Layout.fillWidth: true
            text: bukuKategori
        }

        Label {
            text: "Penerbit"
        }

        Label{
            text: bukuPenerbit
            Layout.fillWidth: true
        }

        Label {
            text: "Jumlah Pengadaan"
        }

        Label {
            Layout.fillWidth: true
            text: bukuJumlahPengadaan
        }

        Label {
            text: "Jumlah Hilang"
        }

        Label {
           Layout.fillWidth: true
           text: bukuJumlahHilang
        }

        Label {
            text: "Jumlah Tidak Hilang"
        }

        Label {
            Layout.fillWidth: true
            text: bukuJumlahPengadaan - bukuJumlahHilang
        }

        Label {
            text: "Jumlah Dipinjam"
        }

        Label {
            Layout.fillWidth: true
            text: bukuJumlahDipinjam
        }

        Label {
            text: "Jumlah Tersedia"
        }

        Label {
            Layout.fillWidth: true
            text: bukuJumlahPengadaan - bukuJumlahHilang - bukuJumlahDipinjam
        }

        Label {
            text: "Tahun Terbit"
        }

        Label {
            Layout.fillWidth: true
            text: bukuTahunTerbit
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
        visible: bukuKode == -1
    }
}
