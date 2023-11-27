import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

Page {
    leftPadding: sidebarRadius

    header: ToolBar{
        RowLayout {
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: "Penerbit"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 20
            }

            SearchField{
                text: viewModel.textQuery
               onTextChanged: viewModel.textQuery = text
            }
        }
    }

    PenerbitViewModel {
        id: viewModel
    }

    RowLayout {
        anchors.fill: parent

        PenerbitList {
            currentViewModel: viewModel
            onAddClicked: {
                editPenerbitDialog.viewModel.configure()
                editPenerbitDialog.open()
            }
        }


        PenerbitDetailFrame {
            currentViewModel: viewModel
            onEditClicked: {
                editPenerbitDialog.viewModel.configure(viewModel.selectedData.kode)
                editPenerbitDialog.open()
            }
            onDeleteClicked: viewModel.removeSelected()
        }

        PenerbitEditDialog {
            id: editPenerbitDialog
        }
    }
}
