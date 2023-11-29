import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../buku"
import "../member"
import "../"

Dialog {
    id: dialog
    property PeminjamanEditViewModel viewModel: PeminjamanEditViewModel {}

    parent: Overlay.overlay
    anchors.centerIn: parent

    modal: true
    title: "Peminjaman Baru"
    standardButtons: Dialog.Ok | Dialog.Cancel

    width: 400
    contentHeight: editPeminjamanDialogLayout.height

    onAccepted: {
        viewModel.submit()
    }

    BukuPilihDialog {
        id: tambahPeminjamanBukuDialog
        title: "Tambah Buku ke Peminjaman"

        onAccepted: {
            dialog.viewModel.appendBuku(viewModel.selectedKode)
        }
    }

    MemberPilihDialog {
        id: memberPilihDialog

        onAccepted: {
            dialog.viewModel.kodeMember = viewModel.selectedKode
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
                    text: viewModel.namaMember
                    readOnly: true
                    Layout.fillWidth: true
                }

                Button {
                    onClicked: {
                        memberPilihDialog.viewModel.init()
                        memberPilihDialog.open()
                    }
                    text: "Ganti"
                }
            }

            DateField {
                title: "Tanggal Peminjaman"
                currentDate: viewModel.tanggalPeminjaman
                id: tanggalPeminjamanTextField
                Layout.fillWidth: true
                onCurrentDateChanged: viewModel.tanggalPeminjaman = currentDate
            }

            AppSpinField {
                title: "Lama"
                suffix: "hari"
                editable: true
                from: 0
                to: 1000
                value: viewModel.lamaPeminjaman
                Layout.fillWidth:true
                onValueChanged: viewModel.lamaPeminjaman = value
            }

            Label {
                text: "Buku"
            }
            Repeater {
                model: viewModel.bukuList

                delegate: Frame {
                    Layout.fillWidth: true

                    ColumnLayout {
                        spacing: 8
                        anchors.fill: parent

                        Label {
                            text: modelData.judul
                        }

                        Button {
                            text: "Hapus"
                            Layout.fillWidth: true
                            onClicked: viewModel.removeBuku(index)
                        }
                    }
                }
            }

            Button {
                visible: viewModel.isBukuAvailable
                text: "Tambah Buku"
                Layout.fillWidth: true
                onClicked: {
                    tambahPeminjamanBukuDialog.viewModel.init()
                    tambahPeminjamanBukuDialog.viewModel.ignoredKode = viewModel.kodeBukuList
                    tambahPeminjamanBukuDialog.open()
                }
            }
        }
    }
}
