import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

BaseDetailFrame {
    property string kategoriKode: ""
    property string kategoriJenis: ""

    signal editClicked()
    signal deleteClicked()

    GridLayout {
        anchors.fill: parent
        columns: 2
        columnSpacing: 16
        visible: kategoriKode != ""

        Text {
            Layout.columnSpan: 2
            text: "Kategori Detail"
            font.pixelSize: 24
        }

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
