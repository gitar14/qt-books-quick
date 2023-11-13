import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

Frame {
    property string peminjamanKode: ""
    property string peminjamanLama: ""
    property date peminjamanTanggal: new Date()
    required property PeminjamanBukuModel peminjamanBukuModel

    signal editClicked()
    signal deleteClicked()

    Layout.minimumWidth: 300
    Layout.maximumWidth: 300
    Layout.fillHeight: true
    Layout.rightMargin: 16
    Layout.topMargin: 16
    Layout.bottomMargin: 16
    padding: 16

    background: Rectangle {
        border.color: "#dedede"
        border.width: 1
        radius: 16
    }

    GridLayout{
        anchors.fill: parent
        columnSpacing: 16
        visible: peminjamanKode !=""
        columns: 2

        Label{
            text: "Tanggal Peminjaman"
        }

        Label{
            text: peminjamanTanggal
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignHCenter

        }

        Label{
            text: "Lama Peminjaman"
        }

        Label{
            text: peminjamanLama
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
