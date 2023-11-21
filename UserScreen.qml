import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Kelompok7.Perpus

Page {
    leftPadding: sidebarRadius

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: "Pegawai"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 20
            }

            SearchField {
                text: userModel.textQuery
                onTextChanged: userModel.textQuery = text
            }
        }
    }


    UserModel {
        id: userModel
    }

    RowLayout {
        anchors.fill: parent

        UserList {
            listModel: userModel
            onAddClicked: {
                userEditDialog.useridUser = ""
                userEditDialog.userNamaDepan = ""
                userEditDialog.userNamaBelakang = ""
                userEditDialog.userPassword = ""
                userEditDialog.userIsNew = true
                userEditDialog.open()
            }

            onCurrentItemDataChanged: {
                if (currentItemData == null) {
                    userDetailFrame.useridUser = ""
                    userDetailFrame.userNamaDepan = ""
                    userDetailFrame.userNamaBelakang = ""
                } else {
                    userDetailFrame.useridUser = currentItemData.idUser
                    userDetailFrame.userNamaDepan = currentItemData.namaDepan
                    userDetailFrame.userNamaBelakang = currentItemData.namaBelakang
                }
            }
        }

        UserDetailFrame {
            id: userDetailFrame
            onEditClicked: {
                userEditDialog.useridUser = useridUser
                userEditDialog.userNamaDepan = userNamaDepan
                userEditDialog.userNamaBelakang = userNamaBelakang
                userEditDialog.userPassword = ""
                userEditDialog.userIsNew = false
                userEditDialog.open()
            }
            onDeleteClicked: userModel.remove(useridUser)
        }


        UserEditDialog{
            id: userEditDialog

            onAccepted: {
                if (userIsNew)
                    userModel.addNew(useridUser, userNamaDepan, userNamaBelakang, userPassword)
                else userModel.edit(
                         useridUser,
                         userNamaDepan,
                         userNamaBelakang
                    )
            }
        }
    }
}

