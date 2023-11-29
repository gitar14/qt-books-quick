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


    SettingViewModel {
        id: viewModel
    }

    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 16

        Control {
            Layout.fillWidth: true
            padding: 16

            background: CardBackground {}
            contentItem: RowLayout {
                Label {
                    Layout.fillWidth: true
                    text: "Denda Keterlambatan Per Hari"
                    font.weight: 500
                }

                SpinBox {
                    Layout.minimumWidth: 200
                    editable: true
                    value: viewModel.dendaPerHari
                    onValueChanged: viewModel.dendaPerHari = value
                    from: 0
                    to: 1000000
                }
            }
        }

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
