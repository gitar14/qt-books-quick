import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    property string userId: ""
    property string userNamaDepan: ""
    property string userNamaBelakang: ""
    property string userPassword: ""
    property string userPasswordUlang: ""

    Frame {
        anchors.centerIn: parent
        width: 384

        ColumnLayout {
            anchors.fill: parent
            Label {
                text: "Buat Akun Admin"
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 20
            }

            Label {
                text: "ID"
            }

            TextField {
                Layout.fillWidth: true
                validator: RegularExpressionValidator {
                    regularExpression: /(?:\d|\w)*/
                }
                maximumLength: 15

                text: userId
                onTextChanged: userId = text
            }

            Label {
                text: "Nama Depan"
            }

            TextField {
                Layout.fillWidth: true
                maximumLength: 25

                text:  userNamaDepan
                onTextChanged: userNamaDepan = text
            }

            Label {
                text: "Nama Belakang"
            }

            TextField {
                Layout.fillWidth: true
                maximumLength: 25

                text: userNamaBelakang
                onTextChanged: userNamaBelakang = text
            }

            Label {
                text: "Password"
            }

            TextField {
                Layout.fillWidth: true
                echoMode: TextInput.Password

                text: userPassword
                onTextChanged: userPassword = text
            }

            Label {
                text: "Ulangi Password"
            }


            TextField {
                Layout.fillWidth: true
                echoMode: TextInput.Password
                text: userPasswordUlang
                onTextChanged: userPasswordUlang = text
            }

            Button {
                Layout.alignment: Qt.AlignRight
                text: "Buat Akun"
                highlighted: true
                enabled: userId.length > 0 &&
                         userNamaDepan.length > 0 &&
                         userNamaBelakang.length > 0 &&
                         userPassword.length > 0 &&
                         userPassword == userPasswordUlang

                onClicked: UserManager.addUser(
                               userId,
                               userNamaDepan,
                               userNamaBelakang,
                               UserManager.AdminRole,
                               userPassword);
            }
        }
    }
}
