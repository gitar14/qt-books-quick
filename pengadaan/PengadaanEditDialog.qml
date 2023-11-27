import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus
import "../buku"
import "../"

Dialog {
    id: dialog
    property PengadaanEditViewModel viewModel: PengadaanEditViewModel {

    }
    onAccepted: {
        viewModel.submit()
    }

    footer : DialogButtonBox {
        Button {
            text: "Batal"
            DialogButtonBox.buttonRole: Dialog.RejectRole
            flat: true
        }
        Button {
            text: "Simpan"
            enabled: viewModel.isValid
            DialogButtonBox.buttonRole: Dialog.AcceptRole
            flat: true
        }
    }

    parent: Overlay.overlay
    anchors.centerIn: parent

    modal: true
    title: "Pengadaan Baru"

    width: 400
    contentHeight: editPengadaanDialogLayout.height

    BukuPilihDialog {
        id: tambahPengadaanBukuDialog
        title: "Tambah Buku ke Pengadaan"

        onAccepted: {
            dialog.viewModel.appendBuku(viewModel.selectedKode)
        }
    }

    Flickable {
        id: editPengadaanDialogFlickable
        anchors.fill: parent
        contentHeight: editPengadaanDialogLayout.height

        ColumnLayout {
            id: editPengadaanDialogLayout
            width: parent.width

            BaseTextField {
                field: viewModel.sumberField
            }

            Label {
                text : "Tanggal"
            }
            DateField {
                currentDate: viewModel.tanggal
                id: tanggalTextField
                Layout.fillWidth: true
                onCurrentDateChanged: viewModel.tanggal = currentDate
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

                        Label {
                            text: "Jumlah"
                        }

                        SpinBox {
                            editable: true
                            from: 0
                            to: 10000
                            value: modelData.jumlah
                            Layout.fillWidth: true
                            onValueChanged: modelData.jumlah = value
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
                enabled: viewModel.isBukuAvailable
                text: enabled ? "Tambah Buku" : "Tidak Ada Buku Tersedia"
                Layout.fillWidth: true
                onClicked: {
                    tambahPengadaanBukuDialog.viewModel.ignoredKode = viewModel.kodeBukuList
                    tambahPengadaanBukuDialog.open()
                }
            }
        }
    }
}
