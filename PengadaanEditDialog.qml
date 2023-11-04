import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import my.id.levirs.books
import Kelompok7.Perpus

Dialog {
    property string pengadaanKode: ""
    property string pengadaanSumber: ""
    required property EditablePengadaanBukuModel pengadaanBukuModel
    required property BookListModel bukuModel

    parent: Overlay.overlay
    anchors.centerIn: parent

    modal: true
    title: "Pengadaan Baru"
    standardButtons: Dialog.Ok | Dialog.Cancel

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
                Layout.fillWidth: true
                text: pengadaanSumber
                onTextChanged: pengadaanSumber = text
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
                visible: bukuModel.count > 0
                text: "Tambah Buku"
                Layout.fillWidth: true
                onClicked: tambahPengadaanBukuDialog.open()
            }
        }
    }
}
