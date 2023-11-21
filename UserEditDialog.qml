import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Dialog {
    parent: Overlay.overlay

    width: 400
    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    modal: true

    property bool userIsNew: false
    property string useridUser: ""
    property string userNamaDepan: ""
    property string userNamaBelakang: ""
    property string userPassword: ""
    property string userPasswordUlang: ""

    title: userIsNew ? "Pegawai" : "Edit User"

    footer: DialogButtonBox {
        Button {
            text: "Batal"
            DialogButtonBox.buttonRole: Dialog.RejectRole
            flat: true
        }
        Button {
            text: "Simpan"
            enabled: userNamaDepan.length > 0 && userNamaBelakang.length > 0
                     && ((userPassword.length > 0 && userPassword == userPasswordUlang) || !userIsNew) && useridUser.length > 0
            DialogButtonBox.buttonRole: Dialog.AcceptRole
            flat: true
        }
    }

    contentHeight: editDialogColumn.height

    Flickable {
        id: editDialogFlickable
        anchors.fill: parent
        clip: true
        contentHeight: editDialogColumn.height

         ColumnLayout {
             id: editDialogColumn

            spacing: 8
            width: parent.width

            Label {
            text: "ID USER"
            }

            TextField {
                id: useridUserTextField
                Layout.fillWidth: true
                text: useridUser
                onTextChanged: useridUser = text
                maximumLength: 25
                readOnly: !userIsNew
            }

            Label {
                Layout.alignment: Qt.AlignRight
                text: (useridUserTextField.maximumLength - useridUser.length) + " tersisa"
            }

            Label {
                color: Material.color(Material.Red)
                text: "ID User tidak boleh kosong"
                visible: useridUser.length == 0
            }

            Label {
                text: "Nama Depan"
            }

            TextField {
                id: userNamaDepanTextField
                Layout.fillWidth: true
                text: userNamaDepan
                onTextChanged: userNamaDepan = text
                maximumLength: 25
            }

            Label {
                Layout.alignment: Qt.AlignRight
                text: (userNamaDepanTextField.maximumLength - userNamaDepan.length) + " tersisa"
            }

            Label {
                color: Material.color(Material.Red)
                text: "Nama Depan tidak boleh kosong"
                visible: userNamaDepan.length == 0
            }

            Label {
                text: "Nama Belakang"
            }

            TextField {
                id: userNamaBelakangTextField
                Layout.fillWidth: true
                text: userNamaBelakang
                onTextChanged: userNamaBelakang = text
                maximumLength: 25
            }

            Label {
                Layout.alignment: Qt.AlignRight
                text: (userNamaBelakangTextField.maximumLength - userNamaBelakang.length) + " tersisa"
            }

            Label {
                color: Material.color(Material.Red)
                text: "Nama Belakang tidak boleh kosong"
                visible: userNamaBelakang.length == 0
            }

            Label {
                visible: userIsNew
                text: "Password"
            }

            TextField {
                visible: userIsNew
                id: userPasswordTextField
                Layout.fillWidth: true
                text: userPassword
                onTextChanged: userPassword = text
                maximumLength: 8
            }

            Label {
                visible: userIsNew
                Layout.alignment: Qt.AlignRight
                text: (userPasswordTextField.maximumLength - userPassword.length) + " tersisa"
            }

            Label{
            text: "Password tidak boleh kosong"
            color: Material.color(Material.Red)
            visible: userIsNew && userPassword.length == 0
            }

            Label {
                text: "Ulangi Password"
            }


            TextField {
                Layout.fillWidth: true
                echoMode: TextInput.Password
                id:userPasswordUlangTextfield
                text: userPasswordUlang
                onTextChanged: userPasswordUlang = text
                maximumLength: 8
            }

            Label {
                text: (userPasswordUlangTextfield.maximumLength - userPasswordUlangTextfield.length) + " tersisa"
                Layout.alignment: Qt.AlignRight
            }

            Label{
            text: "Password harus sama"
            color: Material.color(Material.Red)
            visible: userIsNew && userPasswordUlang != userPassword
            }
        }
    }
}
