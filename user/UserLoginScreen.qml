import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Item {
    signal loggedIn()

    UserLoginViewModel {
        id: viewModel
    }

    Frame {
        anchors.centerIn: parent
        width: 384
        background: CardBackground {}

        ColumnLayout {
            anchors.fill: parent
            Label {
                text: "Login"
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 20
            }

            AppTextField {
                title: "ID"
                showAvailableCount: false
                field: viewModel.idField
                validator: RegularExpressionValidator {
                    regularExpression: /(?:\d|\w)*/
                }
            }

            AppTextField {
                title: "Password"
                showAvailableCount: false
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
