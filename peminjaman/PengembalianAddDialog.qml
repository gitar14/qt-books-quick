import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Dialog {
    id: dialog
    property PengembalianViewModel viewModel: PengembalianViewModel {}

    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 400
    contentHeight: pengembalianDialogLayout.height
    title: "Pengembalian"

    onAccepted: {
        viewModel.submit()
    }

    footer : RowLayout {
        Row {
            leftPadding: 24

            Label {
                text: "Total Denda: "
                font.pixelSize: 16
            }

            Label {
                text: viewModel.denda.totalDenda
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
                currentDate: viewModel.tanggalPengembalian
                onCurrentDateChanged: viewModel.tanggalPengembalian = currentDate
            }

            Label {
                text: "Denda Tenggat"
            }

            Label {
                font.pixelSize: 16
                text: viewModel.denda.totalDendaTerlambat
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
                            text: "Denda"
                        }

                        SpinBox {
                            Layout.fillWidth: true
                            value: modelData.denda
                            onValueChanged: modelData.denda = value
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
