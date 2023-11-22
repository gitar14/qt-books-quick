import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

Page {
    leftPadding: sidebarRadius

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: "Buku"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 20
            }

            SearchField {
                text: listModel.textQuery
                onTextChanged: listModel.textQuery = text
            }
        }
    }

    BookListDetailModel {
        id: detailModel
    }

    BookListModel {
        id: listModel
    }

    KategoriModel {
        id: bukuKategoriModel
    }

    PenerbitModel{
        id: bukuPenerbitModel
    }

    KategoriFilterModel {
        id: bukuKategoriFilterModel
        sourceModel: bukuKategoriModel
    }

    PenerbitFilterModel {
        id: bukuPenerbitFilterModel
        sourceModel: bukuPenerbitModel
    }

    RowLayout {
        anchors.fill: parent

        BukuList {
            listModel: listModel
            kategoriFilterModel: bukuKategoriFilterModel
            penerbitFilterModel: bukuPenerbitFilterModel
            onAddClicked: {
                editDialog.bukuKode = -1
                editDialog.bukuJudul = ""
                editDialog.bukuPenulis = ""
                editDialog.bukuTahunTerbit = 0
                editDialog.bukuKodeKategori = ""
                editDialog.bukuKodePenerbit = ""
                editDialog.open()
            }
            onCurrentItemDataChanged: {
                if (currentItemData == null) {
                    detailModel.kode = -1
                    bukuDetailFrame.bukuJudul = ""
                    bukuDetailFrame.bukuPenulis = ""
                    bukuDetailFrame.bukuTahunTerbit = 0
                    bukuDetailFrame.bukuKategori = ""
                    bukuDetailFrame.bukuPenerbit = ""
                    bukuDetailFrame.bukuPenulis = ""
                } else {
                    detailModel.kode = currentItemData.kode
                    bukuDetailFrame.bukuJudul = currentItemData.judul
                    bukuDetailFrame.bukuPenulis = currentItemData.penulis
                    bukuDetailFrame.bukuTahunTerbit = currentItemData.tahunTerbit
                    bukuDetailFrame.bukuKategori = currentItemData.kategori
                    bukuDetailFrame.bukuPenerbit = currentItemData.penerbit
                    bukuDetailFrame.bukuPenulis = currentItemData.penulis
                }
            }
        }

        BukuDetailFrame {
            id: bukuDetailFrame
            onEditClicked: {
                editDialog.bukuKode = bukuKode
                editDialog.bukuJudul = bukuJudul
                editDialog.bukuPenulis = bukuPenulis
                editDialog.bukuJumlahHilang = detailModel.jumlahHilang
                editDialog.bukuTahunTerbit = bukuTahunTerbit
                editDialog.bukuKodeKategori = detailModel.kodeKategori
                editDialog.bukuKodePenerbit = detailModel.kodePenerbit
                editDialog.open()
            }
            onDeleteClicked: listModel.remove(bukuKode)
            bukuKode: detailModel.kode
            bukuJumlahPengadaan: detailModel.jumlahPengadaan
            bukuJumlahHilang: detailModel.jumlahHilang
            bukuJumlahDipinjam: detailModel.jumlahDipinjam
        }

        BukuEditDialog {
            id: editDialog
            kategoriModel: bukuKategoriModel
            penerbitModel: bukuPenerbitModel
            onAccepted: {
                if (bukuKode == -1)
                    listModel.addNew(
                        bukuJudul,
                        bukuPenulis,
                        bukuTahunTerbit,
                        bukuKodeKategori,
                        bukuKodePenerbit
                    )
                else
                    listModel.edit(
                        bukuKode,
                        bukuJudul,
                        bukuPenulis,
                        bukuJumlahHilang,
                        bukuTahunTerbit,
                        bukuKodeKategori,
                        bukuKodePenerbit
                    )
            }
        }
    }
}
