import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Dialog {
    id: dialog
    property int peminjamanKode: 0
    property date pengembalianTenggat: new Date()
    property date pengembalianTanggal: new Date()
    required property EditablePeminjamanBukuModel peminjamanBukuModel

    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 400
    contentHeight: pengembalianDialogLayout.height
    title: "Pengembalian"


    PeminjamanDendaModel {
        id: peminjamanDendaCalculator
        dendaTambahanBukuList: peminjamanBukuModel.dendaList
        tenggatPengembalian: pengembalianTenggat
        tanggalPengembalian: pengembalianTanggal
    }

    footer : RowLayout {
        Row {
            leftPadding: 24

            Label {
                text: "Total Denda: "
                font.pixelSize: 16
            }

            Label {
                text: peminjamanDendaCalculator.totalDenda
                font.pixelSize: 16
            }
        }

        DialogButtonBox {
            onAccepted: dialog.accept()
            onRejected: dialog.reject()


            Layout.fillWidth: true

            Button {
                text: "Batal"
                DialogButtonBox.buttonRole: Dialog.RejectRole
                flat: true
            }
            Button {
                text: "Simpan"
                DialogButtonBox.buttonRole: Dialog.AcceptRole
                flat: true
            }
        }
    }

    Flickable {
        id: pengembalianDialogFlickable
        anchors.fill: parent
        contentHeight: pengembalianDialogLayout.height

        ColumnLayout {
            id: pengembalianDialogLayout
            width: parent.width

            Label {
                text: "Tanggal Pengembalian"
            }

            DateField {
                Layout.fillWidth: true
                currentDate: pengembalianTanggal
                onCurrentDateChanged: pengembalianTanggal = currentDate
            }

            Label {
                text: "Denda Tenggat"
            }

            Label {
                font.pixelSize: 16
                text: peminjamanDendaCalculator.totalDendaTerlambat
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

                        Label {
                            text: "Denda"
                        }

                        SpinBox {
                            Layout.fillWidth: true
                            value: model.denda
                            onValueChanged: model.denda = value
                            from: 0
                            to: 1000000
                            editable: true
                        }
                    }
                }
            }
        }
    }
}
