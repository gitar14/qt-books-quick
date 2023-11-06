import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    Layout.minimumWidth: 300
    Layout.maximumWidth: 300
    Layout.fillHeight: true
    Layout.rightMargin: 16
    Layout.topMargin: 16
    Layout.bottomMargin: 16
    padding: 16

    property string kategoriKode: ""
    property string kategoriJenis: ""

    signal editClicked()
    signal deleteClicked()

    GridLayout {
        anchors.fill: parent
        columns: 2
        columnSpacing: 16
        visible: kategoriKode != ""

        Label {
            text: "Kode"
        }

        Label {
            Layout.fillWidth: true
            text: kategoriKode
        }

        Label {
            text: "Jenis"
        }

        Label {
            Layout.fillWidth: true
            text: kategoriJenis
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.columnSpan: 2
        }

        RowLayout {
            Layout.columnSpan: 2

            Button {
                text: "Edit"
                onClicked: editClicked()
            }

            Button {
                text: "Hapus"
                onClicked: deleteClicked()
            }
        }
    }

    Label {
        anchors.fill: parent
        visible: kategoriKode == ""

        text: "Tidak ada kategori yang terpilih"
    }
}
