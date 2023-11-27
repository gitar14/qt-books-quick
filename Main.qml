import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import Kelompok7.Perpus

ApplicationWindow {
    width: 960
    height: 640
    visible: true
    title: qsTr("Hello World")

    property int sidebarRadius: 32
    property int sidebarWidth: 250

    Component.onCompleted: {
        TextHighlighter.setHighlightColor(Material.shade(Material.accent, Material.Shade500));
        if (!ConnectionManager.connectByRemembered()) {
            mainStackView.push("ConnectionScreen.qml");
        }
    }

    Connections {
        target: ConnectionManager

        function onConnected() {
            if (!UserManager.hasAvailableUser()) {
                mainStackView.push(userBuatAdmin)
            } else {
                mainStackView.push(userLogin)
            }
        }

        function onConnectionFailed() {
            if (!mainStackView.currentItem)
                mainStackView.push("ConnectionScreen.qml");
        }
    }


    Component {
        id: userBuatAdmin

        UserBuatAdminScreen {
            onUserCreated: {
                mainStackView.push(userLogin)
            }
        }
    }

    Component {
        id: userLogin

        UserLoginScreen {
            onLoggedIn: {
                mainStackView.push("DashboardScreen.qml")
            }
        }
    }

    StackView {
        id: mainStackView
        anchors.fill: parent
    }

}
