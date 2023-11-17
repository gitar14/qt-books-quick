import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    property date pengembalianTanggal: new Date()
    property int pengembalianDenda: 0

    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 400
    title: "Pengembalian"

    standardButtons: Dialog.Ok | Dialog.Cancel

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: "Tanggal Pengembalian"
        }

        DateField {
            Layout.fillWidth: true
            currentDate: pengembalianTanggal
            onCurrentDateChanged: pengembalianTanggal = currentDate
        }

        Label {
            text: "Denda"
        }

        SpinBox {
            Layout.fillWidth: true
            from: 0
            to: 10000000
            editable: true
            value: pengembalianDenda
            onValueChanged: pengembalianDenda = value
        }
    }
}
