import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

Page {
    leftPadding: sidebarRadius
    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: "Member"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
            }

            SearchField {
                text: memberModel.textQuery
                onTextChanged: memberModel.textQuery = text
            }
        }
    }
    MemberModel {
         id: memberModel
    }

    RowLayout {
        anchors.fill: parent
        MemberList {
           listModel: memberModel
           onAddClicked:  {
               editMemberDialog.memberKode = -1
               editMemberDialog.memberNamaDepan = ""
               editMemberDialog.memberNamaBelakang = ""
               editMemberDialog.memberTanggalLahir = new Date()
               editMemberDialog.open()
           }
           onCurrentItemDataChanged: {
               if(currentItemData==null){
                   memberDetailFrame.memberKode = -1
                   memberDetailFrame.memberNamaDepan = ""
                   memberDetailFrame.memberNamaBelakang = ""
                   memberDetailFrame.memberTanggalLahir = ""
               }else{
                   memberDetailFrame.memberKode = currentItemData.kode
                   memberDetailFrame.memberNamaDepan = currentItemData.namaDepan
                   memberDetailFrame.memberNamaBelakang = currentItemData.namaBelakang
                   memberDetailFrame.memberTanggalLahir = currentItemData.tanggalLahir
               }
           }
        }

        MemberDetailFrame{
            id: memberDetailFrame
            onEditClicked: {
                editMemberDialog.memberKode = memberKode
                editMemberDialog.memberNamaDepan = memberNamaDepan
                editMemberDialog.memberNamaBelakang = memberNamaBelakang
                editMemberDialog.memberTanggalLahir = memberTanggalLahir
                editMemberDialog.open()
            }
            onDeleteClicked: memberModel.remove(memberKode)
        }

        MemberEditDialog{
            id: editMemberDialog
            onAccepted:{
                if(memberKode == -1)
                memberModel.add(memberNamaDepan, memberNamaBelakang, memberTanggalLahir)
                else memberModel.edit(memberKode,memberNamaDepan, memberNamaBelakang, memberTanggalLahir)
            }
        }
    }
}
