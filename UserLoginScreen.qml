import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import Kelompok7.Perpus

Item {
    signal loggedIn()

    UserLoginViewModel {
        id: viewModel
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

            BaseTextField {
                field: viewModel.idField
                validator: RegularExpressionValidator {
                    regularExpression: /(?:\d|\w)*/
                }
            }

            BaseTextField {
                field: viewModel.passwordField
                echoMode: TextInput.Password

            }

            Label {
                text: viewModel.errorText
                color: Material.color(Material.Red, Material.Shade500)
                visible: text.length > 0
            }

            Button {
                Layout.alignment: Qt.AlignRight
                text: "Login"
                highlighted: true
                enabled: viewModel.isValid

                onClicked: {
                    if (viewModel.login())
                        loggedIn()
                }
            }
        }
    }
}
