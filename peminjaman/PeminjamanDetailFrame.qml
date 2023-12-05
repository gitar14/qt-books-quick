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

    ColumnLayout {
        anchors.fill: parent
        visible: currentViewModel.hasSelectedItem

        Text {
            text: "Detail Peminjaman"
            font.pixelSize: 24
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            Material.background: "transparent"
            Layout.leftMargin: -16
            Layout.rightMargin: -16

            TabButton {
                text: "Peminjaman"
            }

            TabButton {
                text: "Pengembalian"
            }

            TabButton {
                text: "Buku"
            }
        }

        StackLayout {
            currentIndex: tabBar.currentIndex
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 8
            Layout.bottomMargin: 8

            ColumnLayout {
                Label{
                    text: "Nama Member"
                }

                Label{
                    text: currentViewModel.selectedData.namaMember
                    font.bold: true
                }

                Label {
                    text: "Pengawas"
                }

                Label {
                    text: currentViewModel.selectedData.peminjamanUserNama
                    font.bold: true
                }

                Label{
                    text: "Tanggal Peminjaman"
                }

                Label{
                    text: Qt.formatDate(currentViewModel.selectedData.tanggalPeminjaman, locale, Locale.LongFormat)
                    font.bold: true
                }

                Label{
                    text: "Lama Peminjaman"
                }

                Label{
                    text: currentViewModel.selectedData.lamaPeminjaman + " hari"
                    font.bold: true
                }

                Label {
                    text: "Tanggal Tenggat"
                }

                Label {
                    text: Qt.formatDate(currentViewModel.selectedData.tenggatPengembalian, locale, Locale.LongFormat)
                    font.bold: true
                }

                Label {
                    text: "Status"
                }

                Label {
                    font.bold: true
                    text: currentViewModel.selectedData.sudahDikembalikan ? "Sudah Dikembalikan" : "Belum Dikembalikan"
                }
            }

            ColumnLayout {
                Label {
                    visible: !currentViewModel.selectedData.sudahDikembalikan
                    text: "Belum Dikembalikan"
                }

                Label {
                    visible: currentViewModel.selectedData.sudahDikembalikan
                    text: "Pengawas"
                }

                Label {
                    visible: currentViewModel.selectedData.sudahDikembalikan
                    text: currentViewModel.selectedData.pengembalianUserNama
                    font.bold: true
                }

                Label {
                    visible: currentViewModel.selectedData.sudahDikembalikan
                    text: "Tanggal Pengembalian"
                }

                Label {
                    visible: currentViewModel.selectedData.sudahDikembalikan
                    text: Qt.formatDate(currentViewModel.selectedData.tanggalPengembalian, locale, Locale.LongFormat)
                    font.bold: true
                }

                GridLayout {
                    visible: currentViewModel.selectedData.sudahDikembalikan
                    columns: 2
                    Layout.fillWidth: true

                    Label {
                        text: "Denda Keterlambatan"
                        Layout.fillWidth: true
                    }

                    Label {
                        Layout.alignment: Qt.AlignRight
                        text: currentViewModel.selectedDenda.totalDendaTerlambat
                    }

                    Label {
                        text: "Total Denda"
                    }

                    Label {
                        Layout.alignment: Qt.AlignRight
                        text: currentViewModel.selectedDenda.totalDenda
                    }
                }
            }

            ListView {
                id: bukuListView
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: currentViewModel.selectedBukuList
                spacing: 8
                clip: true

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
                            font.bold: true
                            text: modelData.judul
                        }

                        Label {
                            visible: modelData.denda
                            text: "Denda: " + modelData.denda
                        }
                    }
                }
            }
        }

        Button {
            Layout.alignment: Qt.AlignRight
            visible: !currentViewModel.selectedData.sudahDikembalikan
            text: "Tandai Dikembalikan"
            onClicked: tandaiDikembalikanClicked()
            Material.accent: Material.primary
            highlighted: true
        }

        Button {
            Layout.alignment: Qt.AlignRight
            visible: currentViewModel.selectedData.sudahDikembalikan
            text: "Tandai Belum Dikembalikan"
            onClicked: tandaiBelumDikembalikanClicked()
            highlighted: true
            Material.accent: Material.Red
        }

        Row {
            Layout.alignment: Qt.AlignRight
            spacing: 8

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
        text: "Tidak ada peminjaman yang terpilih"
        visible: !currentViewModel.hasSelectedItem
    }
}
