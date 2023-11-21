import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

BaseDetailFrame {
    property int bukuKode: -1
    property string bukuJudul: ""
    property string bukuPenulis: ""
    property string bukuKategori: ""
    property string bukuPenerbit: ""
    property int bukuJumlahBuku: 0
    property int bukuTahunTerbit: 0

    signal editClicked()
    signal deleteClicked()


    GridLayout {
        anchors.fill: parent
        columns: 2
        columnSpacing: 16
        visible: bukuKode != -1

        Text {
            Layout.columnSpan: 2
            text: "Detail Buku"
            font.pixelSize: 24
        }

        Text {
            text: "Kode"
        }

        Text {
            Layout.fillWidth: true
            text: bukuKode
        }

        Text {
            text: "Judul"
        }

        Text {
            Layout.fillWidth: true
            text: bukuJudul
        }

        Text {
            text: "Penulis"
        }

        Text {
            Layout.fillWidth: true
            text: bukuPenulis
        }

        Text {
            text: "Kategori"
        }

        Text {
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

        Text {
            text: "Jumlah Buku"
        }

        Text {
            Layout.fillWidth: true
            text: bukuJumlahBuku
        }

        Text {
            text: "Tahun Terbit"
        }

        Text {
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
