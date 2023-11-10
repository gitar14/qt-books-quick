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
            }

            SearchField{
//                text: penerbitModel.textQuery
//                onTextChanged: penerbitModel.textQuery = text
            }
        }
    }
    PenerbitModel {
        id: penerbitModel
    }

    RowLayout {
        anchors.fill: parent

        PenerbitList {
            listModel: penerbitModel
            onAddClicked: {
                editPenerbitDialog.penerbitKode = ""
                editPenerbitDialog.penerbitNama = ""
                editPenerbitDialog.penerbitAlamat = ""
                editPenerbitDialog.open()
            }
            onCurrentItemDataChanged: {
                if (currentItemData == null) {
                    penerbitDetailFrame.penerbitKode = ""
                    penerbitDetailFrame.penerbitNama = ""
                    penerbitDetailFrame.penerbitAlamat = ""
                } else {
                    penerbitDetailFrame.penerbitKode = currentItemData.kode
                    penerbitDetailFrame.penerbitNama = currentItemData.name
                    penerbitDetailFrame.penerbitAlamat = currentItemData.alamat
                }
            }
        }


        PenerbitDetailFrame {
            id: penerbitDetailFrame
            onEditClicked: {
                editPenerbitDialog.penerbitKode = penerbitKode
                editPenerbitDialog.penerbitNama = penerbitNama
                editPenerbitDialog.penerbitAlamat = penerbitAlamat
                editPenerbitDialog.open()
            }
            onDeleteClicked: penerbitModel.remove(penerbitKode)
        }

        PenerbitEditDialog {
            id: editPenerbitDialog

            onAccepted: {
                if(penerbitKode == "")
                    penerbitModel.add(penerbitNama, penerbitAlamat)
                else penerbitModel.edit(penerbitKode, penerbitNama, penerbitAlamat)
            }
        }
    }
}
