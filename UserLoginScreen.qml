import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    property string userId: ""
    property string userPassword: ""
    property string lastError: ""

    Connections {
        target: UserManager

        function onLoginFailed(reason) {
            lastError = reason
        }
    }

    Frame {
        anchors.centerIn: parent
        width: 384

        ColumnLayout {
            anchors.fill: parent
            Label {
                text: "Login"
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
                text: "Password"
            }

            TextField {
                Layout.fillWidth: true
                echoMode: TextInput.Password

                text: userPassword
                onTextChanged: userPassword = text
            }

            Label {
                text: lastError
                color: Material.color(Material.Red, Material.Shade500)
                visible: lastError.length > 0
            }

            Button {
                Layout.alignment: Qt.AlignRight
                text: "Login"
                highlighted: true
                enabled: userId.length > 0 &&
                         userPassword.length > 0

                onClicked: UserManager.login(
                               userId,
                               userPassword);
            }
        }
    }
}
