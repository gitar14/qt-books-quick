import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
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
                text: "Pegawai"
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


    UserPegawaiViewModel {
        id: viewModel
    }

    RowLayout {
        anchors.fill: parent

        UserList {
            currentViewModel: viewModel
            onAddClicked: {
                userEditDialog.viewModel.configure()
                userEditDialog.open()
            }
        }

        UserDetailFrame {
            currentViewModel: viewModel
            id: userDetailFrame
            onEditClicked: {
                userEditDialog.viewModel.configure(viewModel.selectedData.id)
                userEditDialog.open()
            }
            onDeleteClicked: viewModel.removeSelected()
        }


        UserEditDialog{
            id: userEditDialog
        }
    }
}

