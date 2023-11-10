import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Page {
    leftPadding: sidebarRadius

    header: ToolBar {
        Label {
            anchors.fill: parent
            text: "Pengaturan"
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            font.pixelSize: 20
        }
    }


    SettingsModel {
        id: settingModel
    }

    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 16

        CardDelegate {
            Layout.fillWidth: true
            text: "Bersihkan Konfigurasi Koneksi"
            onClicked: ConnectionManager.clearRememberedConfiguration();
        }

        CardDelegate {
            Layout.fillWidth: true
            text: "Bersihkan Database"
            onClicked: {
                settingModel.clearDatabase();
            }
        }
    }
}
