import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Page {
    leftPadding: sidebarRadius
    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: sidebarRadius

            Label {
                Layout.fillWidth: true
                text: "Pengadaan"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 20
            }

            SearchField {
                text: viewModel.textQuery
                onTextChanged: viewModel.textQuery = text
            }
        }
    }

    PengadaanViewModel {
        id: viewModel
    }

    RowLayout{
        anchors.fill: parent

        PengadaanList {
            currentViewModel: viewModel
            onAddClicked: {
                editPengadaanDialog.viewModel.configure()
                editPengadaanDialog.open()
            }
        }

    PengadaanDetailFrame {
        id: pengadaanDetailFrame
        currentViewModel: viewModel
        onEditClicked: {
            editPengadaanDialog.viewModel.configure(viewModel.selectedData.kode)
            editPengadaanDialog.open();
        }
        onDeleteClicked: {
            viewModel.removeSelectedItem()
        }
    }

    PengadaanEditDialog {
        id: editPengadaanDialog
    }
    }
}
