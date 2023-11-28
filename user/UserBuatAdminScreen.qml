import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Kelompok7.Perpus
import "../"

Item {
    signal userCreated()

    UserBuatAdminViewModel {
        id: viewModel
    }

    Frame {
        anchors.centerIn: parent
        width: 384
        height: Math.min(parent.height - 64, columnLayout.height)

        Flickable {
            contentHeight: columnLayout.height
            clip: true
            anchors.fill: parent

            ColumnLayout {
                id: columnLayout
                width: parent.width

                Label {
                    text: "Buat Akun Admin"
                    Layout.alignment: Qt.AlignHCenter
                    font.pixelSize: 20
                }

                AppTextField {
                    title: "ID"
                    field: viewModel.idField
                    validator: RegularExpressionValidator {
                        regularExpression: /(?:\d|\w)*/
                    }
                }

                AppTextField {
                    title: "Nama Depan"
                    field: viewModel.namaDepanField
                }

                AppTextField {
                    title: "Nama Belakang"
                    field: viewModel.namaBelakakngField
                }

                AppTextField {
                    title: "Password"
                    field: viewModel.password
                    echoMode: TextInput.Password
                }

                AppTextField {
                    title: "Password Ulang"
                    field: viewModel.passwordUlang
                    echoMode: TextInput.Password
                }

                Button {
                    Layout.alignment: Qt.AlignRight
                    text: "Buat Akun"
                    highlighted: true
                    enabled: viewModel.isValid
                    onClicked: {
                        viewModel.submit()
                        userCreated()
                    }
                }
            }
        }
    }
}
