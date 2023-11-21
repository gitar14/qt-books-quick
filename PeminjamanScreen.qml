import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Page {
    leftPadding: sidebarRadius

    header: ToolBar {
        RowLayout{
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: "Peminjaman"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 20
            }

            SearchField {
//                 text: peminjamanBukuModel.textQuery
//                 onTextChanged: peminjamanBukuModel.textQuery = text
            }
        }
    }

    PeminjamanBukuModel {
        id: peminjamanBukuModel
        kodePeminjaman: peminjamanDetailFrame.peminjamanKode
    }

    EditablePeminjamanBukuModel {
        id: editablePeminjamanBukuModel
        onItemsChanged: peminjamanBukuListModel.setIgnoredKodeList(kodeBukuList)
    }

    PeminjamanModel {
        id: peminjamanModel
    }

    BookListModel {
        id: peminjamanBukuListModel
    }

    MemberModel {
        id: memberModel
    }

    RowLayout {
        anchors.fill: parent

        PeminjamanList {
            listModel: peminjamanModel
            onAddClicked: {
                editPeminjamanDialog.peminjamanKode = -1
                editPeminjamanDialog.peminjamanMemberKode = -1
                editPeminjamanDialog.peminjamanMemberNama = ""
                editPeminjamanDialog.peminjamanLama = 0
                editPeminjamanDialog.peminjamanTanggal = new Date()
                editablePeminjamanBukuModel.clear();
                editPeminjamanDialog.open()
            }
            onCurrentItemDataChanged: {
                if(currentItemData != null){
                    peminjamanDetailFrame.peminjamanKode = currentItemData.kode
                    peminjamanDetailFrame.peminjamanMemberKode = currentItemData.kodeMember
                    peminjamanDetailFrame.peminjamanMemberNama = currentItemData.namaMember
                    peminjamanDetailFrame.peminjamanLama = currentItemData.lama
                    peminjamanDetailFrame.peminjamanTanggal = currentItemData.tanggal
                    peminjamanDetailFrame.peminjamanTanggalTenggat = currentItemData.tanggalTenggat
                    peminjamanDetailFrame.peminjamanTanggalPengembalian = currentItemData.tanggalPengembalian
                    peminjamanDetailFrame.peminjamanSudahDikembalikan = currentItemData.sudahDikembalikan
                } else {
                    peminjamanDetailFrame.peminjamanKode = -1
                    peminjamanDetailFrame.peminjamanMemberKode = -1
                    peminjamanDetailFrame.peminjamanMemberNama = ""
                    peminjamanDetailFrame.peminjamanLama = 0
                    peminjamanDetailFrame.peminjamanTanggal = new Date()
                    peminjamanDetailFrame.peminjamanTanggalTenggat = new Date()
                    peminjamanDetailFrame.peminjamanTanggalPengembalian = new Date()
                    peminjamanDetailFrame.peminjamanSudahDikembalikan = false
                }
            }
        }

        PeminjamanEditDialog{
            id: editPeminjamanDialog
            peminjamanBukuModel: editablePeminjamanBukuModel
            bukuModel: peminjamanBukuListModel
            memberModel: memberModel
            onAccepted: {
                if (peminjamanKode == -1) {
                    peminjamanKode = peminjamanModel.add(peminjamanMemberKode, peminjamanTanggal, peminjamanLama)
                    peminjamanBukuModel.addAll(peminjamanKode, editablePeminjamanBukuModel);
                } else {
                    peminjamanModel.update(peminjamanKode, peminjamanMemberKode, peminjamanTanggal, peminjamanLama);
                    peminjamanBukuModel.updateAll(editablePeminjamanBukuModel)
                }
            }
        }

        PengembalianAddDialog {
            id: dialogPengembalian
            peminjamanBukuModel: editablePeminjamanBukuModel

            onAccepted: {
                peminjamanModel.tandaiDikembalikan(peminjamanDetailFrame.peminjamanKode, pengembalianTanggal)
                peminjamanBukuModel.updateAll(editablePeminjamanBukuModel)
            }
        }

        PeminjamanDetailFrame{
            id: peminjamanDetailFrame
            peminjamanBukuModel: peminjamanBukuModel
            onEditClicked: {
                editPeminjamanDialog.peminjamanKode = peminjamanKode
                editPeminjamanDialog.peminjamanMemberKode = peminjamanMemberKode
                editPeminjamanDialog.peminjamanMemberNama = peminjamanMemberNama
                editPeminjamanDialog.peminjamanLama = peminjamanLama
                editPeminjamanDialog.peminjamanTanggal = peminjamanTanggal
                editablePeminjamanBukuModel.populateFrom(peminjamanBukuModel);
                editPeminjamanDialog.open();
            }

            onDeleteClicked: {
                peminjamanBukuModel.removeAll();
                peminjamanModel.remove(peminjamanKode);
            }

            onTandaiDikembalikanClicked: {
                dialogPengembalian.pengembalianTanggal = new Date()
                editablePeminjamanBukuModel.populateFrom(peminjamanBukuModel)
                dialogPengembalian.open()
            }

            onTandaiBelumDikembalikanClicked: {
                peminjamanModel.tandaiBelumDikembalikan(peminjamanKode)
                peminjamanBukuModel.resetDenda()
            }
        }
    }
}
