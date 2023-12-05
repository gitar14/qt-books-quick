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
            anchors.leftMargin: sidebarRadius

            Label {
                Layout.fillWidth: true
                text: "Member"
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

    MemberViewModel {
         id: viewModel
    }

    RowLayout {
        anchors.fill: parent
        MemberList {
           currentViewModel: viewModel
           onAddClicked:  {
               editMemberDialog.viewModel.configure()
               editMemberDialog.open()
           }
        }

        MemberDetailFrame{
            currentViewModel: viewModel
            onEditClicked: {
                editMemberDialog.viewModel.configure(viewModel.selectedData.kode)
                editMemberDialog.open()
            }
            onDeleteClicked: viewModel.removeSelectedItem()
        }

        MemberEditDialog{
            id: editMemberDialog
        }
    }
}
