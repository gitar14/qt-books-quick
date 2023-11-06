import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Kelompok7.Perpus

RowLayout {
    MemberModel{
         id: memberModel
    }

    MemberList{
       listModel: memberModel
       onAddClicked:  {
           editMemberDialog.memberKode = ""
           editMemberDialog.memberNamaDepan = ""
           editMemberDialog.memberNamaBelakang = ""
           editMemberDialog.memberTanggalLahir = new Date()
           editMemberDialog.open()
       }
       onCurrentItemDataChanged: {
           if(currentItemData==null){
               memberDetailFrame.memberKode = ""
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
            if(memberKode=="")
            memberModel.add(memberNamaDepan, memberNamaBelakang, memberTanggalLahir)
            else memberModel.edit(memberKode,memberNamaDepan, memberNamaBelakang, memberTanggalLahir)
        }
    }
}
