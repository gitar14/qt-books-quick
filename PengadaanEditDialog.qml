import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus

Dialog {
    property int pengadaanKode: -1
    property string pengadaanSumber: ""
    property date pengadaanTanggal: new Date ()
    required property EditablePengadaanBukuModel pengadaanBukuModel
    required property BookListModel bukuModel

    footer : DialogButtonBox {
        Button {
            text: "Batal"
            DialogButtonBox.buttonRole: Dialog.RejectRole
            flat: true
        }
        Button {
            text: "Simpan"
            enabled: pengadaanSumber.length > 0
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
        listModel: bukuModel

        onAccepted: {
            pengadaanBukuModel.append(
                bukuModel.getKodeByIndex(selectedIndex),
                0
            )
        }
    }

    Flickable {
        id: editPengadaanDialogFlickable
        anchors.fill: parent
        contentHeight: editPengadaanDialogLayout.height

        ColumnLayout {
            id: editPengadaanDialogLayout
            width: parent.width

            Label {
                text: "Sumber"
            }
            TextField {
                id: pengadaanSumberTextField
                Layout.fillWidth: true
                maximumLength: 25
                text: pengadaanSumber
                onTextChanged: pengadaanSumber = text
            }

            Label {
                Layout.alignment: Qt.AlignRight
                text: (pengadaanSumberTextField.maximumLength - pengadaanSumber.length) + " tersisa"
            }

            Label {
                text: "Sumber Tidak Boleh Kosong"
                color: Material.color(Material.Red)
                visible: pengadaanSumber.length == 0
            }

            Label {
                text : "Tanggal"
            }
            DateField {
                currentDate: editPengadaanDialog.pengadaanTanggal
                id: tanggalTextField
                Layout.fillWidth: true
                onCurrentDateChanged: editPengadaanDialog.pengadaanTanggal = currentDate
            }
            Label {
                text: "Buku"
            }
            Repeater {
                model: pengadaanBukuModel

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
                            onClicked: pengadaanBukuModel.remove(index)
                        }
                    }

                }
            }
            Button {
                enabled: pengadaanBukuModel.isBukuAvailable
                text: enabled ? "Tambah Buku" : "Tidak Ada Buku Tersedia"
                Layout.fillWidth: true
                onClicked: tambahPengadaanBukuDialog.open()
            }
        }
    }
}
