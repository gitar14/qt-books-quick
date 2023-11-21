import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Dialog {
    property int peminjamanKode: -1
    property int peminjamanMemberKode: -1
    property string peminjamanMemberNama: ""
    property int peminjamanLama: 0
    property date peminjamanTanggal: new Date ()
    required property EditablePeminjamanBukuModel peminjamanBukuModel
    required property BookListModel bukuModel
    required property MemberModel memberModel

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

        onAccepted: {
            peminjamanBukuModel.append(
                bukuModel.getKodeByIndex(selectedIndex)
                )
            }
    }

    MemberPilihDialog {
        id: memberPilihDialog
        listModel: memberModel

        onAccepted: {
            peminjamanMemberKode = currentItemData.kode
            peminjamanMemberNama = currentItemData.name
        }
    }

    Flickable {
        id: editPeminjamanDialogFlickable
        anchors.fill: parent
        contentHeight: editPeminjamanDialogLayout.height

        ColumnLayout {
            id: editPeminjamanDialogLayout
            width: parent.width

            Label {
                text: "Member"
            }

            RowLayout {
                Layout.fillWidth: true

                TextField {
                    text: peminjamanMemberNama
                    readOnly: true
                    Layout.fillWidth: true
                }

                Button {
                    onClicked: memberPilihDialog.open()
                    text: "Ganti"
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
                value: peminjamanLama
                Layout.fillWidth:true
                onValueChanged: peminjamanLama = value
            }

            Label {
                text: "Buku"
            }
            Repeater {
                model: peminjamanBukuModel

                delegate: Frame {
                    Layout.fillWidth: true

                    ColumnLayout {
                        spacing: 8
                        anchors.fill: parent

                        Label {
                            text: model.judulBuku
                        }

                        Button {
                            text: "Hapus"
                            Layout.fillWidth: true
                            onClicked: peminjamanBukuModel.remove(index)
                        }
                    }
                }
            }

            Button {
                visible: peminjamanBukuModel.isBukuAvailable
                text: "Tambah Buku"
                Layout.fillWidth: true
                onClicked: tambahPeminjamanBukuDialog.open()
            }
        }
    }
}
