import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

BaseDetailFrame {
    property BukuViewModel currentViewModel

    signal editClicked()
    signal deleteClicked()


    ColumnLayout {
        anchors.fill: parent
        visible: currentViewModel.hasSelectedItem

        Label {
            text: "Detail Buku"
            font.pixelSize: 24
        }

        TabBar {
            id: tabBar
            Layout.leftMargin: -16
            Layout.rightMargin: -16
            Layout.fillWidth: true
            Material.background: "transparent"


            TabButton {
                text: "Dasar"
            }

            TabButton {
                text: "Ketersediaan"
            }
        }

        StackLayout {
            currentIndex: tabBar.currentIndex
            Layout.topMargin: 8
            Layout.bottomMargin: 8

            ColumnLayout {
                Label {
                    text: "Judul"
                }

                Label {
                    text: currentViewModel.selectedData.judul
                    font.bold: true
                }

                Label {
                    text: "Penulis"
                }

                Label {
                    text: currentViewModel.selectedData.penulis
                    font.bold: true
                }

                Label {
                    text: "Kategori"
                }

                Label {
                    text: currentViewModel.selectedData.namaKategori
                    font.bold: true
                }

                Label {
                    text: "Penerbit"
                }

                Label{
                    text: currentViewModel.selectedData.namaPenerbit
                    Layout.fillWidth: true
                    font.bold: true
                }

                Label {
                    text: "Tahun Terbit"
                }

                Label {
                    text: currentViewModel.selectedData.tahunTerbit
                    font.bold: true
                }
            }

            GridLayout {
                Layout.fillWidth: true
                columns: 2

                Label {
                    Layout.fillWidth: true
                    text: "Jumlah Pengadaan"
                }

                Label {
                    Layout.alignment: Qt.AlignRight
                    text: currentViewModel.selectedDataJumlah.pengadaan
                }

                Label {
                    Layout.fillWidth: true
                    text: "Jumlah Hilang"
                }

                Label {
                   Layout.alignment: Qt.AlignRight
                   text: currentViewModel.selectedData.jumlahHilang
                }

                Label {
                    Layout.fillWidth: true
                    text: "Jumlah Tidak Hilang"
                }

                Label {
                    Layout.alignment: Qt.AlignRight
                    text: currentViewModel.selectedDataJumlah.tidakHilang
                }

                Label {
                    Layout.fillWidth: true
                    text: "Jumlah Dipinjam"
                }

                Label {
                    Layout.alignment: Qt.AlignRight
                    text: currentViewModel.selectedDataJumlah.dipinjam
                }

                Label {
                    Layout.fillWidth: true
                    text: "Jumlah Tersedia"
                }

                Label {
                    Layout.alignment: Qt.AlignRight
                    text: currentViewModel.selectedDataJumlah.tersedia
                }
            }

        }

        RowLayout {
            Layout.alignment: Qt.AlignRight

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
        text: "Tidak ada buku yang terpilih"
        visible: !currentViewModel.hasSelectedItem
    }
}
