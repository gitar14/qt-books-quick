import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import my.id.levirs.books
import Kelompok7.Perpus

Dialog {
    property string peminjamanKode: ""
    property string peminjamanSumber: ""
    property date peminjamanTanggal: new Date ()
//    required property EditablePeminjamanBukuModel peminjamanBukuModel
    required property BookListModel bukuModel

    parent: Overlay.overlay
    anchors.centerIn: parent

    modal: true
    title: "Peminjaman Baru"
    standardButtons: Dialog.Ok | Dialog.Cancel

    width: 400
    contentHeight: editPeminjamanDialogLayout.height

    BukuPilihDialog {
        id: tambahPeminjamanBukuDialog
        title: "Tambah Buku ke Peminjaman"
        listModel: bukuModel

//        onAccepted: {
//            peminjamanBukuModel.append(
//                bukuModel.getKodeByIndex(selectedIndex)
//                        0
//                )
//            }
    }

    Flickable {
        id: editPeminjamanDialogFlickable
        anchors.fill: parent
        contentHeight: editPeminjamanDialogLayout.height

        ColumnLayout {
            id: editPeminjamanDialogLayout
            width: parent.width

            Repeater {
//                model: peminjamanBukuModel

                delegate: Frame {
                    Layout.fillWidth: true

                    ColumnLayout {
                        spacing: 8
                        anchors.fill: parent

                        Label {
                            text: model.judulBuku
                        }

                        Label {
                            text: "Jumlah"
                        }

                        SpinBox {
                            editable: true
                            from: 0
                            to: 10000
                            value: model.jumlah
                            Layout.fillWidth: true
                            onValueChanged: model.jumlah = value
                        }

                        Button {
                            text: "Hapus"
                            Layout.fillWidth: true
                            onClicked: peminjamanBukuModel.remove(index)
                        }
                    }
                }
            }

            Label {
                text: "Tanggal Peminjaman"
            }
            DateField {
                currentDate: editPeminjamanDialog.peminjamanTanggal
                id: tanggalPeminjamanTextField
                Layout.fillWidth: true
                onCurrentDateChanged: editPeminjamanDialog.peminjamanTanggal = currentDate
            }

            Label {
                text: "Lama Peminjaman"
            }
            SpinBox {
                editable: true
                from: 0
                to: 1000
                //value: model.lama
                Layout.fillWidth:true
//                onValueChanged: model.lama = value
            }

            Label {
                text: "Buku"
            }

            Button {
//                visible: bukuModel.count > 0
                text: "Tambah Buku"
                Layout.fillWidth: true
                onClicked: tambahPeminjamanBukuDialog.open()
            }
        }
    }
}
