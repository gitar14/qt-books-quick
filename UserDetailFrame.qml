import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

BaseDetailFrame {
    property string useridUser: ""
    property string userNamaDepan: ""
    property string userNamaBelakang: ""

    signal editClicked()
    signal deleteClicked()

    GridLayout {
        anchors.fill: parent
        columns: 2
        columnSpacing: 16
        visible: useridUser != ""

        Label {
            text: "ID User"
        }

        Label {
            Layout.fillWidth: true
            text: useridUser
        }

        Label {
            text: "Nama Depan"
        }

        Label {
            Layout.fillWidth: true
            text: userNamaDepan
        }

        Label {
            text: "Nama Belakang"
        }

        Label {
            Layout.fillWidth: true
            text: userNamaBelakang
        }

        Item {
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
        visible: useridUser == ""

        text: "Tidak ada user yang terpilih"
    }
}
