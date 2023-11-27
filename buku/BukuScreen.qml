import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus
import "../"

Page {
    leftPadding: sidebarRadius

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: "Buku"
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

    BukuViewModel {
        id: viewModel
    }

    RowLayout {
        anchors.fill: parent

        BukuList {
            currentViewModel: viewModel
            onAddClicked: {
                editDialog.viewModel.configure()
                editDialog.open()
            }
        }

        BukuDetailFrame {
            id: bukuDetailFrame
            currentViewModel: viewModel
            onEditClicked: {
                editDialog.viewModel.configure(viewModel.selectedData.kode)
                editDialog.open()
            }
            onDeleteClicked: listModel.remove(bukuKode)
        }

        BukuEditDialog {
            id: editDialog
        }
    }
}
